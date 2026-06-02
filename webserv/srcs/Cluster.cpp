/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/02 21:01:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

extern volatile sig_atomic_t	g_stop;

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Cluster::Cluster() :
	_servers(),
	_clients(),
	_fds(),
	_pipeToClientMap(),
	_cgiBuffs()
{
}

Cluster::~Cluster()
{
	// Close active clients
	std::map<int, Server *>::iterator	it_cli;
	for (it_cli = _clients.begin(); it_cli != _clients.end(); ++it_cli)
	{
		close(it_cli->first);
	}

	// Free allocated servers
	std::map<int, Server *>::iterator	it_serv;
	for (it_serv = _servers.begin(); it_serv != _servers.end(); ++it_serv)
	{
		delete it_serv->second;
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Cluster::_addNewConnection(int serv_fd)
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(client_addr);

	// 1. Accept the incoming connection
	int		client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &addr_len);

	if (client_fd < 0)
	{
		perror("accept failed");
		return;
	}

	// 2. Make the client socket non-blocking
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fctnl O_NONBLOCK failed");
		close(client_fd);
		return;
	}

	// 3. Add client to the master poll list to monitor reading (POLLIN)
	struct pollfd	pfd;
	pfd.fd = client_fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_fds.push_back(pfd);

	// 4. Route this client to the specific virtual server that accepted it
	_clients[client_fd] = _servers[serv_fd];

	std::cout << "[Cluster] New connection accepted on fd " << client_fd << std::endl;
}

void
Cluster::_handleClientRead(int fd, Server &server)
{
	// Delegate reading to the server
	ReadStatus	status = server.handleRead(fd);

	if (status <= CLIENT_READ_ERROR)
		_closeConnection(fd);
	else if (status == CLIENT_STATIC_READY)
	{
		// Static file ready: Switch client from POLLIN to POLLOUT
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLOUT;
				break;
			}
		}
	}
	else if (status == CGI_PROCESS_READY)
	{
		std::cout << "[Cluster] CGI mode activated for client fd " << fd << std::endl;

		int				cgi_write_fd = server.getWriteFd(fd);
		int				cgi_read_fd = server.getReadFd(fd);

		struct pollfd	pfd_write;
		pfd_write.fd = cgi_write_fd;
		pfd_write.events = POLLOUT;
		pfd_write.revents = 0;
		_fds.push_back(pfd_write);

		struct pollfd	pfd_read;
		pfd_read.fd = cgi_read_fd;
		pfd_read.events = POLLIN;
		pfd_read.revents = 0;
		_fds.push_back(pfd_read);

		_pipeToClientMap[cgi_write_fd] = fd;
		_pipeToClientMap[cgi_read_fd] = fd;
	}
}

void
Cluster::_handleClientWrite(int fd, Server &server)
{
	// Delegate sending to the server
	int	status = server.handleWrite(fd);

	if (status <= 0)
		_closeConnection(fd);
	else if (status == 2)
	{
		// Response sent. Switch back to POLLIN to wait for the next request (Keep-Alive)
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLIN;
				break;
			}
		}
	}
}

void
Cluster::_closeConnection(int fd)
{
	std::map<int, int>::iterator	it = _pipeToClientMap.begin();
	while (it != _pipeToClientMap.end())
	{
		if (it->second == fd)
		{
			int		pipe_fd = it->first;
			close(pipe_fd);
			_removePipeFromPoll(pipe_fd);
			_cgiBytesWritten.erase(pipe_fd);

			// Safe post-increment erase for map iteration
			_pipeToClientMap.erase(it++);
		}
		else
			++it;
	}
	close(fd);
	_removePipeFromPoll(fd);
	_clients.erase(fd);
	_cgiBuffs.erase(fd);

	std::cout << "[Cluster] Connection closed on fd " << fd << std::endl;
}

void
Cluster::_handleCGIWrite(int pipe_write_fd, Server &server)
{
	int			client_fd = _pipeToClientMap[pipe_write_fd];

	std::cout << "[Cluster] Sending data to CGI input pipe " << pipe_write_fd << std::endl;

	std::string	body = server.getRequestBody(client_fd);
	// Handle Edge Case: If the request body is empty, execute immediate pipe closure
	if (body.empty())
	{
		close(pipe_write_fd);
		for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
		{
			if (it->fd == pipe_write_fd)
			{
				_fds.erase(it);
				break;
			}
		}
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

	size_t		already_written = _cgiBytesWritten[pipe_write_fd];

	std::cout << "[Cluster] Sending data chunk to CGI input pipe " << pipe_write_fd
			  << " (" << already_written << "/" << body.size() << " bytes)" << std::endl;

	int			ret = write(pipe_write_fd, body.c_str() + already_written,
							body.size() - already_written);
	// Error Handling: If write returns an error or pipe is broken, clean up the client connection
	if (ret <= 0)
	{
		_closeConnection(client_fd);
		close(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

	_cgiBytesWritten[pipe_write_fd] += ret;

	if (_cgiBytesWritten[pipe_write_fd] == body.size())
	{
		std::cout << "[Cluster] All data sent successfully to CGI pipe " << pipe_write_fd << std::endl;

		close(pipe_write_fd);
		for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
		{
			if (it->fd == pipe_write_fd)
			{
				_fds.erase(it);
				break;
			}
		}
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
	}
}

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	std::cout << "[Cluster] Getting output from CGI pipe " << pipe_read_fd << std::endl;

	char	buff[4096];
	int		client_fd = _pipeToClientMap[pipe_read_fd];
	int		bytes_read = read(pipe_read_fd, buff, sizeof(buff) - 1);

	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffs[client_fd] += std::string(buff, bytes_read); // Accumulate raw script output
		return;
	}
	if (bytes_read < 0)
	{
		std::cerr << "[Cluster] CGI read error (process killed)" << std::endl;

		Response	err_res;
		err_res.defaultErrorPage(503);
		server.setCgiResponse(client_fd, err_res);

		close(pipe_read_fd);
		_removePipeFromPoll(pipe_read_fd);
		_pipeToClientMap.erase(pipe_read_fd);
		_cgiBuffs.erase(client_fd);

		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == client_fd)
			{
				_fds[i].events = POLLOUT;
				break;
			}
		}
		return;
	}

	// bytes_read <= 0 means the CGI script has finished execution and closed its pipe
	std::string	cgiOutput = _cgiBuffs[client_fd];
	_cgiBuffs.erase(client_fd);

	close(pipe_read_fd);

	// Clean up the CGI tracking infrastructure
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == pipe_read_fd)
		{
			_fds.erase(it);
			break;
		}
	}
	_pipeToClientMap.erase(pipe_read_fd);

	// Parse the script output to extract potential headers and body
	Response	response;
	size_t		headerEnd = cgiOutput.find("\r\n\r\n");

	if (headerEnd != std::string::npos)
	{
		std::string	headersPart = cgiOutput.substr(0, headerEnd);
		std::string	bodyPart = cgiOutput.substr(headerEnd + 4);

		response.setStatus(200);
		response.setBody(bodyPart);

		// Simple parser to extract Content-Type header generated by Python
		size_t	ctPos = headersPart.find("Content-Type:");
		if (ctPos != std::string::npos)
		{
			size_t	lineEnd = headersPart.find("\r\n", ctPos);
			std::string	ctValue = headersPart.substr(ctPos + 13, lineEnd - (ctPos + 13));
			response.setHeader("Content-Type", Utils::trim(ctValue));
		}
		else
			response.setHeader("Content-Type", "text/html");
	}
	else
	{
		// Fallback if script output lacks clean HTTP headers
		response.setStatus(200);
		response.setBody(cgiOutput);
		response.setHeader("Content-Type", "text/html");
	}
	server.setCgiResponse(client_fd, response);

	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == client_fd)
		{
			_fds[i].events = POLLOUT;
			break;
		}
	}
}

void
Cluster::_removePipeFromPoll(int pipe_fd)
{
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == pipe_fd)
		{
			_fds.erase(it);
			break;
		}
	}
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Cluster::setup(std::vector<Config> configs)
{
	for (size_t i = 0; i < configs.size(); ++i)
	{
		Server	*server = new Server(configs[i]);
		server->setup(); // Opens, binds, and listens the server socket

		int	serv_fd = server->getServerFd();
		_servers[serv_fd] = server;

		struct pollfd	pfd;
		pfd.fd = serv_fd;
		pfd.events = POLLIN; // Monitor incoming connections
		pfd.revents = 0;
		_fds.push_back(pfd);

		std::cout << "[Cluster] Server listening on port " << configs[i].getPort() << std::endl;
	}
}

void
Cluster::run()
{
	while (g_stop == 0)
	{
		if (poll(&_fds[0], _fds.size(), -1) < 0)
		{
			if (g_stop == 0)
				perror("poll error");
			continue;
		}
		for (size_t i = 0; i < _fds.size(); )
		{
			int	fd = _fds[i].fd;

			// Handle reading and new connections
			if ((_fds[i].revents & POLLIN) ||
			   ((_fds[i].revents & POLLHUP) &&
			   _pipeToClientMap.count(fd) &&
			   _fds[i].events == POLLIN))
			{
				if (_servers.count(fd))
					_addNewConnection(fd);
				else if (_pipeToClientMap.count(fd)) // 1. CGI internal read pipe
				{
					int	client_fd = _pipeToClientMap[fd];
					_handleCGIRead(fd, *_clients[client_fd]);
				}
				else if (_clients.count(fd))         // 2. True external client socket
					_handleClientRead(fd, *_clients[fd]);
			}
			// Handle outgoing data transmission
			else if (_fds[i].revents & POLLOUT)
			{
				if (_pipeToClientMap.count(fd))      // 1. CGI internal write pipe
				{
					int	client_fd = _pipeToClientMap[fd];
					_handleCGIWrite(fd, *_clients[client_fd]);
				}
				else if (_clients.count(fd))         // 2. True external client socket
					_handleClientWrite(fd, *_clients[fd]);
			}
			// Handle errors or sudden disconnections
			else if (_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
				_closeConnection(fd);

			// Safely increment index if the current file descriptor wasn't erased
			if (i < _fds.size() && _fds[i].fd == fd)
				++i;
		}
	}
}
