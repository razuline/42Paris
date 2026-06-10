/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/10 14:55:34 by erazumov         ###   ########.fr       */
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
	// Close active clients sockets safely
	std::map<int, Server *>::iterator	it_cli;
	for (it_cli = _clients.begin(); it_cli != _clients.end(); ++it_cli)
	{
		close(it_cli->first);
	}

	// Free dynamically allocated virtual servers
	std::map<int, Server *>::iterator	it_serv;
	for (it_serv = _servers.begin(); it_serv != _servers.end(); ++it_serv)
	{
		delete it_serv->second;
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

		int		serv_fd = server->getServerFd();
		_servers[serv_fd] = server;

		struct	pollfd pfd;
		pfd.fd = serv_fd;
		pfd.events = POLLIN; // Monitor incoming connections
		pfd.revents = 0;
		_fds.push_back(pfd);

		std::stringstream	ss;
		ss << "Server virtual host listening on port ["
		   << configs[i].getPort() << "]";

		Utils::logInfo(ss.str());
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
		for (size_t i = 0; i < _fds.size();)
		{
			int	fd = _fds[i].fd;

			if (_fds[i].revents == 0)
			{
				++i;
				continue;
			}

			// A. Handle incoming data multiplexing
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
				else if (_clients.count(fd)) // 2. True external client socket
					_handleClientRead(fd, *_clients[fd]);
			}
			// B. Handle outgoing data transmission multiplexing
			else if (_fds[i].revents & POLLOUT)
			{
				if (_pipeToClientMap.count(fd)) // 1. CGI internal write pipe
				{
					int	client_fd = _pipeToClientMap[fd];
					_handleCGIWrite(fd, *_clients[client_fd]);
				}
				else if (_clients.count(fd)) // 2. True external client socket
					_handleClientWrite(fd, *_clients[fd]);
			}
			// C. Handle network errors or unexpected hang-ups
			else if (_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (_pipeToClientMap.count(fd))
				{
					int	pipe_fd = fd;
					close(pipe_fd);
					_removePipeFromPoll(pipe_fd);
					_cgiBytesWritten.erase(pipe_fd);
					_pipeToClientMap.erase(pipe_fd);
				}
				else
				{
					_closeConnection(fd);
				}
			}
			else
			{
				if (_clients.count(fd))
					_closeConnection(fd);
				else
					++i;
			}
			// Safely skip index increment if current fd was erased from vector
			if (i < _fds.size() && _fds[i].fd == fd)
				++i;
		}
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Cluster::_addNewConnection(int serv_fd)
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(client_addr);

	// 1. Accept the incoming TCP connection
	int	client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &addr_len);
	if (client_fd < 0)
	{
		perror("accept failed");
		return;
	}

	// 2. Prevent socket operations from blocking the main loop
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fctnl O_NONBLOCK failed");
		close(client_fd);
		return;
	}

	// 3. Register client socket to monitor reading events (POLLIN)
	struct pollfd	pfd;
	pfd.fd = client_fd;
	pfd.events = POLLIN;
	pfd.revents = 0;
	_fds.push_back(pfd);

	// 4. Bind client socket descriptor to its respective virtual server
	_clients[client_fd] = _servers[serv_fd];

	std::cout << "[Cluster] Connection accepted on client fd [" << client_fd
			  << "]" << std::endl;
}

void
Cluster::_handleClientRead(int fd, Server &server)
{
	// Process non-blocking request reading stream
	Server::ReadStatus	status = server.handleRead(fd);

	std::cout << "[Cluster] handleRead on fd [" << fd << "] status code: "
			  << static_cast<int>(status) << std::endl;

	if (status <= Server::READ_ERROR)
		_closeConnection(fd);
	else if (status == Server::STATIC_READY)
	{
		// Parsing complete: Toggle poll event from POLLIN to POLLOUT to transmit response
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLOUT;
				break;
			}
		}
	}
	else if (status == Server::CGI_READY)
	{
		std::cout << "[Cluster] CGI pipe pooling activated for client fd ["
				  << fd << "]" << std::endl;

		int	cgi_write_fd = server.getWriteFd(fd);
		int	cgi_read_fd = server.getReadFd(fd);

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
	// Inspect the exact transmission metrics returned by the non-blocking socket
	Server::WriteStatus	status = server.handleWrite(fd);

	if (status == Server::WRITE_ERROR)
	{
		_closeConnection(fd);
	}
	else if (status == Server::WRITE_COMPLETE)
	{
		std::cout << "[Cluster] Success response sent. Resetting client fd ["
				  << fd << "] back to POLLIN" << std::endl;

		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLIN;
				_fds[i].revents = 0;
				break;
			}
		}

		// Clear context and instantly fire the next pipelined request if it's already complete
		Server::ReadStatus	next_status = server.clearClientState(fd);
		if (next_status == Server::STATIC_READY)
		{
			for (size_t i = 0; i < _fds.size(); ++i)
			{
				if (_fds[i].fd == fd)
				{
					_fds[i].events = POLLOUT; // Stay in write mode for the pipelined request immediately
					break;
				}
			}
		}
		else if (next_status == Server::CGI_READY)
		{
			int	cgi_write_fd = server.getWriteFd(fd);
			int	cgi_read_fd = server.getReadFd(fd);

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
}

void
Cluster::_closeConnection(int fd)
{
	// Purge remaining orphaned CGI pipes mapped to this specific client
	std::map<int, int>::iterator	it = _pipeToClientMap.begin();
	while (it != _pipeToClientMap.end())
	{
		if (it->second == fd)
		{
			int	pipe_fd = it->first;
			close(pipe_fd);
			_removePipeFromPoll(pipe_fd);
			_cgiBytesWritten.erase(pipe_fd);
			_pipeToClientMap.erase(it++);
		}
		else
			++it;
	}
	if (_clients.count(fd))
		_clients[fd]->clearClientState(fd);

	close(fd);
	_removePipeFromPoll(fd);
	_clients.erase(fd);
	_cgiBuffs.erase(fd);

	std::cout << "[Cluster] Connection securely closed on fd [" << fd
			  << "]" << std::endl;
}

void
Cluster::_handleCGIWrite(int pipe_write_fd, Server &server)
{
	int					client_fd = _pipeToClientMap[pipe_write_fd];
	const std::string	&body = server.getRequestBody(client_fd);

	// Clean up and exit immediately if there's no body payload to transmit
	if (body.empty())
	{
		close(pipe_write_fd);
		_removePipeFromPoll(pipe_write_fd);
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

	// Transmit the payload chunk over the non-blocking pipe
	size_t	already_written = _cgiBytesWritten[pipe_write_fd];
	size_t	to_write = body.size() - already_written;

	if (to_write > 8192)
		to_write = 8192;

	int	ret = write(pipe_write_fd, body.c_str() + already_written, to_write);

	// Error Handling: Drop the client connection if the write pipe breaks
	if (ret > 0)
	{
		_cgiBytesWritten[pipe_write_fd] += ret;

		// Close write end of the pipe once the entire request payload is transmitted
		if (_cgiBytesWritten[pipe_write_fd] == body.size())
		{
			std::cout << "[Cluster] Body chunk successfully pushed to CGI pipe ["
					  << pipe_write_fd << "]" << std::endl;

			close(pipe_write_fd);
			_removePipeFromPoll(pipe_write_fd);
			_pipeToClientMap.erase(pipe_write_fd);
			_cgiBytesWritten.erase(pipe_write_fd);
		}
	}
}

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	std::cout << "[Cluster] Getting output from CGI pipe " << pipe_read_fd
			  << std::endl;

	char	buff[4096];
	int		client_fd = _pipeToClientMap[pipe_read_fd];
	int		bytes_read = read(pipe_read_fd, buff, sizeof(buff) - 1);

	// Accumulate incoming script execution stream bytes
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffs[client_fd] += std::string(buff, bytes_read); // Accumulate raw script output
		return;
	}
	// Fault Tolerance: Script crashed or was killed
	if (bytes_read < 0)
	{
		std::cerr << "[Cluster] CGI pipe crash detected. Sending HTTP [500]"
				  << std::endl;

		Response	err_res;
		err_res.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
		server.setCgiResponse(client_fd, err_res);

		close(pipe_read_fd);
		_removePipeFromPoll(pipe_read_fd);
		_pipeToClientMap.erase(pipe_read_fd);
		_cgiBuffs.erase(client_fd);

		// Switch client event monitor to POLLOUT to transmit the error page
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

	// Script finished successfully - parse output
	std::string	cgiOutput = _cgiBuffs[client_fd];

	_cgiBuffs.erase(client_fd);

	close(pipe_read_fd);
	_removePipeFromPoll(pipe_read_fd);
	_pipeToClientMap.erase(pipe_read_fd);

	server.cleanupCgi(client_fd);

	// Parse CGI output
	Response	response;
	size_t		headerEnd = cgiOutput.find("\r\n\r\n");

	if (headerEnd != std::string::npos)
	{
		// Case 1: Headers + body
		std::string	headersPart = cgiOutput.substr(0, headerEnd);
		std::string	bodyPart = cgiOutput.substr(headerEnd + 4);

		response.setBody(bodyPart); // This sets Content-Length automatically

		int					cgi_status_code = Http::OK;
		bool				has_content_type = false;
		bool				has_location = false;
		std::string			location_url;

		std::stringstream	header_ss(headersPart);
		std::string			line;

		// Parse headers line by line
		while (std::getline(header_ss, line))
		{
			// Remove trailing \r if present
			if (!line.empty() && line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);
			if (line.empty())
				continue;

			size_t	colon = line.find(':');
			if (colon != std::string::npos)
			{
				std::string	key = Utils::trim(line.substr(0, colon));
				std::string	value = Utils::trim(line.substr(colon + 1));

				if (key == "Status")
				{
					// Parse status code (e.g., "Status: 404 Not Found")
					std::stringstream	status_ss(value);
					status_ss >> cgi_status_code;
				}
				else if (key == "Location")
				{
					has_location = true;
					location_url = value;
					response.setHeader("Location", value);
				}
				else
				{
					if (key == "Content-Type")
						has_content_type = true;
					response.setHeader(key, value); // Forward location, cookies, etc.
				}
			}
		}
		// CGI RFC: If Location header is present without Status, it's a 302 redirect
		if (has_location && cgi_status_code == Http::OK)
		{
			cgi_status_code = Http::FOUND;
		}
		response.setStatus(cgi_status_code);

		// Set default Content-Type if missing
		if (!has_content_type && !has_location && !bodyPart.empty())
		{
			response.setHeader("Content-Type", "text/html");
		}

		// For redirects, ensure no body is sent
		if (has_location && (cgi_status_code == Http::FOUND ||
							 cgi_status_code == Http::MOVED_PERMANENTLY))
		{
			response.setBody(""); // Clear body, Content-Length becomes 0
		}
	}
	else if (!cgiOutput.empty())
	{
		// Case 2: No headers, just raw output (treat as HTML)
		response.setStatus(Http::OK);
		response.setBody(cgiOutput); // This sets Content-Length automatically
		response.setHeader("Content-Type", "text/html");
	}
	else
	{
		// Case 3: Empty response
		response.setStatus(Http::NO_CONTENT);
		response.setBody(""); // Content-Length: 0
	}

	// Ensure Content-Length is always set (Response::setBody already does this)
	// But double-check for edge cases
	if (response.getStatus() == Http::NO_CONTENT ||
	   (response.getStatus() >= 300 && response.getStatus() < 400))
	{
		// For 204 No Content and 3xx redirects, ensure no body
		response.setBody("");
	}

	std::cout << "\033[33m[DEBUG CGI] Server built response for client:\033[0m"
			  << std::endl;
	std::cout << "  -> Status Code: " << response.getStatus() << std::endl;

	server.setCgiResponse(client_fd, response);

	// Switch target client socket back to POLLOUT
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
	std::vector<struct pollfd>::iterator	it;
	for (it = _fds.begin(); it != _fds.end(); ++it)
	{
		if (it->fd == pipe_fd)
		{
			_fds.erase(it);
			break;
		}
	}
}
