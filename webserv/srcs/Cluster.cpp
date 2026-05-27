/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/27 18:28:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Cluster::Cluster()
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
	int	status = server.handleRead(fd);

	if (status <= 0)
		_closeConnection(fd);
	else if (status == 2)
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
	else if (status == 3)
	{
		std::cout << "[Cluster] CGI mode activated for client fd " << fd << std::endl;

		// 1. Get the pipe fds from the server's CGI instance
		int				cgi_write_fd = server.getWriteFd(fd);
		int				cgi_read_fd = server.getReadFd(fd);

		// 2. Add the CGI write pipe to the main poll array
		struct pollfd	pfd_write;
		pfd_write.fd = cgi_write_fd;
		pfd_write.events = POLLOUT;
		pfd_write.revents = 0;
		_fds.push_back(pfd_write);

		// 3. Add the CGI read pipe to the main poll array
		struct pollfd	pfd_read;
		pfd_read.fd = cgi_read_fd;
		pfd_read.events = POLLIN;
		pfd_read.revents = 0;
		_fds.push_back(pfd_read);

		// 4. Link new FDs to the right server in maps so Cluster knows who they belong to
		_clients[cgi_write_fd] = &server;
		_clients[cgi_read_fd] = &server;
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
	// 1. Close the system file descriptor
	close(fd);

	// 2. Remove from the global poll array
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == fd)
		{
			_fds.erase(it);
			break;
		}
	}
	_clients.erase(fd);
	std::cout << "[Cluster] Connection closed on fd " << fd << std::endl;
}

void
Cluster::_handleCGIWrite(int pipe_write_fd, Server &server)
{
	std::cout << "[Cluster] Sending data to CGI input pipe " << pipe_write_fd << std::endl;

	std::string	body = "";

	if (!body.empty())
		write(pipe_write_fd, body.c_str(), body.size());

	// 1. Close the write pipe so Python gets EOF and executes
	close(pipe_write_fd);

	// 2. Remove ONLY this write pipe from the poll array so we stop monitoring it
	for (std::vector<struct pollfd>::iterator it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == pipe_write_fd)
		{
			_fds.erase(it);
			break;
		}
	}
	// Remove the mapping for this specific pipe descriptor
	_clients.erase(pipe_write_fd);
}

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	std::cout << "[Cluster] Getting output from CGI pipe " << pipe_read_fd << std::endl;

	char	buff[4096];
	int		client_fd = _pipeToClientMap[pipe_fd]; // Map linking CGI pipe to client socket
	int		bytes_read = read(pipe_fd, buff, sizeof(buff) - 1);

	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffers[client_fd] += std::string(buff, bytes_read); // Accumulate raw script output
	}
	else
	{
		// bytes_read <= 0 means the CGI script has finished execution and closed its pipe
		std::string	cgiOutput = _cgiBuffers[client_fd];
		_cgiBuffers.erase(client_fd);

		// Clean up the CGI tracking infrastructure
		_removePipeFromPoll(pipe_fd);
		delete _cgis[client_fd];
		_cgis.erase(client_fd);

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

		// Save response and switch client socket state to POLLOUT (Write state = 2)
		_resps[client_fd] = response;
		_clientStates[client_fd] = 2;
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
		size_t	curr_size = _fds.size(); // Protected from iteration shift
		for (size_t i = 0; i < curr_size; ++i)
		{
			int	fd = _fds[i].fd;

			// Handle reading and new connections
			if (_fds[i].revents & POLLIN)
			{
				if (_servers.count(fd))
					_addNewConnection(fd);
				else if (_clients.count(fd))
				{
					// Check if this fd is actually the CGI read pipe
					if (fd == _clients[fd]->getReadFd(fd))
						_handleCGIRead(fd, *_clients[fd]);
					else
						_handleClientRead(fd, *_clients[fd]);
				}
			}
			// Handle writing responses
			else if (_fds[i].revents & POLLOUT)
			{
				if (_clients.count(fd))
				{
					// Check if this fd is actually the CGI write pipe
					if (fd == _clients[fd]->getWriteFd(fd))
						_handleCGIWrite(fd, *_clients[fd]);
					else
						_handleClientWrite(fd, *_clients[fd]);
				}
			}
			// Handle errors or sudden disconnections
			else if (_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
				_closeConnection(fd);
		}
	}
}
