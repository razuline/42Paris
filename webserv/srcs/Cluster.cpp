/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/08 18:44:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

extern volatile sig_atomic_t	g_stop;

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Cluster::Cluster() : _servers(),
					 _clients(),
					 _fds(),
					 _pipeToClientMap(),
					 _cgiBuffs()
{
}

Cluster::~Cluster()
{
	// Close active clients sockets safely
	std::map<int, Server *>::iterator it_cli;
	for (it_cli = _clients.begin(); it_cli != _clients.end(); ++it_cli)
	{
		close(it_cli->first);
	}

	// Free dynamically allocated virtual servers
	std::map<int, Server *>::iterator it_serv;
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
		Server *server = new Server(configs[i]);
		server->setup(); // Opens, binds, and listens the server socket

		int serv_fd = server->getServerFd();
		_servers[serv_fd] = server;

		struct pollfd pfd;
		pfd.fd = serv_fd;
		pfd.events = POLLIN; // Monitor incoming connections
		pfd.revents = 0;
		_fds.push_back(pfd);

		std::cout << "[Cluster] Server virtual host listening on port ["
				  << configs[i].getPort() << "]" << std::endl;
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
			int fd = _fds[i].fd;

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
					int client_fd = _pipeToClientMap[fd];
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
					int client_fd = _pipeToClientMap[fd];
					_handleCGIWrite(fd, *_clients[client_fd]);
				}
				else if (_clients.count(fd)) // 2. True external client socket
					_handleClientWrite(fd, *_clients[fd]);
			}
			// C. Handle network errors or unexpected hang-ups
			else if (_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (_pipeToClientMap.count(fd))
					_closeConnection(_pipeToClientMap[fd]);
				else
					_closeConnection(fd);
			}

			// Safely skip index increment if current file descriptor was erased from vector
			if (i < _fds.size() && _fds[i].fd == fd)
				++i;
		}
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Cluster::_addNewConnection(int serv_fd)
{
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(client_addr);

	// 1. Accept the incoming TCP connection
	int client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &addr_len);

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
	struct pollfd pfd;
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
	Server::ReadStatus status = server.handleRead(fd);

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

		int cgi_write_fd = server.getWriteFd(fd);
		int cgi_read_fd = server.getReadFd(fd);

		struct pollfd pfd_write;
		pfd_write.fd = cgi_write_fd;
		pfd_write.events = POLLOUT;
		pfd_write.revents = 0;
		_fds.push_back(pfd_write);

		struct pollfd pfd_read;
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

	// Clear state and check if a pipelined request is already prepared to fire
	Server::ReadStatus next_status = server.clearClientState(fd);
	if (next_status == Server::STATIC_READY)
	{
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLOUT;
				break;
			}
		}
	}
	else if (next_status == Server::CGI_READY)
	{
		int cgi_write_fd = server.getWriteFd(fd);
		int cgi_read_fd = server.getReadFd(fd);

		struct pollfd pfd_write;
		pfd_write.fd = cgi_write_fd;
		pfd_write.events = POLLOUT;
		pfd_write.revents = 0;
		_fds.push_back(pfd_write);

		struct pollfd pfd_read;
		pfd_read.fd = cgi_read_fd;
		pfd_read.events = POLLIN;
		pfd_read.revents = 0;
		_fds.push_back(pfd_read);

		_pipeToClientMap[cgi_write_fd] = fd;
		_pipeToClientMap[cgi_read_fd] = fd;
	}
}

void
Cluster::_closeConnection(int fd)
{
	// Purge remaining orphaned CGI pipes mapped to this specific client
	std::map<int, int>::iterator it = _pipeToClientMap.begin();
	while (it != _pipeToClientMap.end())
	{
		if (it->second == fd)
		{
			int pipe_fd = it->first;
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

	std::cout << "[Cluster] Connection securely closed on fd [" << fd << "]" << std::endl;
}

void
Cluster::_handleCGIWrite(int pipe_write_fd, Server &server)
{
	int client_fd = _pipeToClientMap[pipe_write_fd];
	std::string body = server.getRequestBody(client_fd);

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
	size_t already_written = _cgiBytesWritten[pipe_write_fd];

	int ret = write(pipe_write_fd, body.c_str() + already_written,
					body.size() - already_written);

	// Error Handling: Drop the client connection if the write pipe breaks
	if (ret <= 0)
	{
		_closeConnection(client_fd);
		close(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

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

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	std::cout << "[Cluster] Getting output from CGI pipe " << pipe_read_fd << std::endl;

	char buff[4096];
	int client_fd = _pipeToClientMap[pipe_read_fd];
	int bytes_read = read(pipe_read_fd, buff, sizeof(buff) - 1);

	// Accumulate incoming script execution stream bytes
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffs[client_fd] += std::string(buff, bytes_read); // Accumulate raw script output
		return;
	}
	// Fault Tolerance: Script crashed or was killed (Returns SC_503 Service Unavailable)
	if (bytes_read < 0)
	{
		std::cerr << "[Cluster] CGI pipe crash detected. Sending HTTP [503]" << std::endl;

		Response err_res;
		err_res.defaultErrorPage(Http::OK);
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

	// Python script closed its write end: execution finished successfully
	std::string cgiOutput = _cgiBuffs[client_fd];
	_cgiBuffs.erase(client_fd);

	close(pipe_read_fd);
	_removePipeFromPoll(pipe_read_fd);
	_pipeToClientMap.erase(pipe_read_fd);

	server.cleanupCgi(client_fd);

	// Parse the script output stream to extract headers and payload
	Response response;
	size_t headerEnd = cgiOutput.find("\r\n\r\n");

	if (headerEnd != std::string::npos)
	{
		std::string headersPart = cgiOutput.substr(0, headerEnd);
		std::string bodyPart = cgiOutput.substr(headerEnd + 4);

		response.setBody(bodyPart);

		int cgi_status_code = Http::OK;
		bool has_content_type = false;
		bool has_location = false;

		std::stringstream header_ss(headersPart);
		std::string line;

		// Extract custom gateway headers line by line
		while (std::getline(header_ss, line))
		{
			if (!line.empty() && line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);
			if (line.empty())
				continue;

			size_t colon = line.find(':');
			if (colon != std::string::npos)
			{
				std::string key = Utils::trim(line.substr(0, colon));
				std::string value = Utils::trim(line.substr(colon + 1));

				if (key == "Status")
				{
					std::stringstream status_ss(value);
					status_ss >> cgi_status_code;
				}
				else
				{
					if (key == "Content-Type")
						has_content_type = true;
					if (key == "Location")
						has_location = true;
					response.setHeader(key, value); // Forward location, cookies, etc.
				}
			}
		}
		// CGI RFC Specification: Force 302 Redirect if Location header is present without Status
		if (cgi_status_code == Http::OK && has_location)
			cgi_status_code = Http::FOUND;

		response.setStatus(cgi_status_code);

		// Fallback content-type metadata to safeguard browsers rendering
		if (!has_content_type)
			response.setHeader("Content-Type", "text/html");
	}
	else
	{
		// Raw script execution fallback if no headers are provided
		response.setStatus(Http::OK);
		response.setBody(cgiOutput);
		response.setHeader("Content-Type", "text/html");
	}

	server.setCgiResponse(client_fd, response);

	// Set target client socket back to POLLOUT to transmit data back to the client
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
