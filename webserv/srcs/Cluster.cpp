/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/13 18:56:30 by erazumov         ###   ########.fr       */
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
	_cgiBuffs(),
	_cgiBytesWritten(),
	_cgiStartTime(),
	_pendingCgiReadFd(),
	_active_cgis(0)
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

		// Check for CGI timeouts
		time_t	now = time(NULL);
		std::map<int, time_t>::iterator	it = _cgiStartTime.begin();
		while (it != _cgiStartTime.end())
		{
			if (now - it->second > 300)
			{
				std::cerr << "[Cluster] CGI timeout for client_fd " << it->first
						  << std::endl;

				// Kill the CGI process
				if (_clients.count(it->first))
				{
					_clients[it->first]->cleanupCgi(it->first);

					// Send 504 Gateway Timeout
					Response	err_res;
					err_res.defaultErrorPage(Http::GATEWAY_TIMEOUT);
					_clients[it->first]->setCgiResponse(it->first, err_res);

					// Switch client to POLLOUT
					for (size_t i = 0; i < _fds.size(); ++i)
					{
						if (_fds[i].fd == it->first)
						{
							_fds[i].events = POLLOUT;
							break;
						}
					}
				}
				_cgiStartTime.erase(it++);
			}
			else
			{
				++it;
			}
		}

		// 1. Snapshot all file descriptors that received an event
		std::vector<int>	ready_fds;
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].revents != 0)
				ready_fds.push_back(_fds[i].fd);
		}
		// 2. Process each ready fd using live safe indices
		for (size_t k = 0; k < ready_fds.size(); ++k)
		{
			int	curr_fd = ready_fds[k];

			// Dynamically locate where curr_fd sits right now in the vector
			size_t	live_idx = 0;
			bool	found = false;
			for (; live_idx < _fds.size(); ++live_idx)
			{
				if (_fds[live_idx].fd == curr_fd)
				{
					found = true;
					break;
				}
			}
			if (!found)
				continue; // Skipped safely if closed or removed by a previous event action

			short	revents = _fds[live_idx].revents;
			short	events = _fds[live_idx].events;
			if (revents == 0)
				continue;

			// A. Handle incoming data multiplexing
			if (((revents & POLLIN) && (events & POLLIN)) ||
				((revents & POLLHUP) && (events & POLLIN)))
			{
				if (_servers.count(curr_fd))
					_addNewConnection(curr_fd);
				else if (_pipeToClientMap.count(curr_fd))
				{
					int	client_fd = _pipeToClientMap[curr_fd];
					_handleCGIRead(curr_fd, *_clients[client_fd]);
				}
				else if (_clients.count(curr_fd))
					_handleClientRead(curr_fd, *_clients[curr_fd]);
			}
			// B. Handle outgoing data transmission multiplexing
			else if ((revents & POLLOUT) && (events & POLLOUT))
			{
				if (_pipeToClientMap.count(curr_fd))
				{
					int	client_fd = _pipeToClientMap[curr_fd];
					_handleCGIWrite(curr_fd, *_clients[client_fd]);
				}
				else if (_clients.count(curr_fd))
					_handleClientWrite(curr_fd, *_clients[curr_fd]);
			}
			// C. Handle network errors or unexpected hang-ups
			else if (revents & (POLLERR | POLLHUP | POLLNVAL))
			{
				if (_pipeToClientMap.count(curr_fd))
				{
					close(curr_fd);
					_removePipeFromPoll(curr_fd);
					_cgiBytesWritten.erase(curr_fd);
					_pipeToClientMap.erase(curr_fd);
				}
				else if (_clients.count(curr_fd))
				{
					if (events & POLLIN)
					{
						_closeConnection(curr_fd);
					}
				}
			}
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
	{
		std::cout << "[Cluster] READ_ERROR, closing connection fd " << fd
				  << std::endl;

		_closeConnection(fd);
	}
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
		int	cgi_write_fd = server.getWriteFd(fd);
		int	cgi_read_fd = server.getReadFd(fd);

		// Record CGI start time
		_cgiStartTime[fd] = time(NULL);

		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = 0; // Temporarily mute client socket triggers
				break;
			}
		}

		// ONLY add the write pipe initially
		struct pollfd pfd_write;
		pfd_write.fd = cgi_write_fd;
		pfd_write.events = POLLOUT;
		pfd_write.revents = 0;
		_fds.push_back(pfd_write);

		_pipeToClientMap[cgi_write_fd] = fd;

		struct pollfd	pfd_read;
		pfd_read.fd = cgi_read_fd;
		pfd_read.events = POLLIN;
		pfd_read.revents = 0;
		_fds.push_back(pfd_read);
		_pipeToClientMap[cgi_read_fd] = fd;

		_pendingCgiReadFd.erase(fd);

		std::cout << "[Cluster] Added both write and read CGI pipes to poll "
				  << "simultaneously" << std::endl;
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

		// Reset to POLLIN to wait for next request
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLIN;
				_fds[i].revents = 0;
				break;
			}
		}
		server.clearClientState(fd);
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

	if (body.empty())
	{
		close(pipe_write_fd);
		_removePipeFromPoll(pipe_write_fd);
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

	size_t	already_written = _cgiBytesWritten[pipe_write_fd];
	size_t	remaining = body.size() - already_written;

	if (remaining == 0)
	{
		// Close write pipe to signal EOF to CGI
		close(pipe_write_fd);
		_removePipeFromPoll(pipe_write_fd);
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
		return;
	}

	size_t	to_write = remaining;
	if (to_write > 65536)
		to_write = 65536;

	size_t	total_chunk_written = 0;
	int		fail_counter = 0;

	while (total_chunk_written < to_write)
	{
		int	ret = write(pipe_write_fd,
						body.c_str() + already_written + total_chunk_written,
						to_write - total_chunk_written);

		if (ret > 0)
		{
			total_chunk_written += ret;
			fail_counter = 0;
		}
		else if (ret == 0 || (ret < 0 && total_chunk_written > 0))
		{
			usleep(10);
			if (++fail_counter > 5000)
				break;
		}
		else
		{
			break;
		}
	}

	_cgiBytesWritten[pipe_write_fd] += total_chunk_written;

	if (_cgiBytesWritten[pipe_write_fd] == body.size())
	{
		std::cout << "[Cluster] Complete body written to CGI pipe ("
				  << body.size() << " bytes)" << std::endl;

		close(pipe_write_fd);
		_removePipeFromPoll(pipe_write_fd);
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
	}
}

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	char	buff[4096];
	int		client_fd = _pipeToClientMap[pipe_read_fd];
	int		bytes_read = read(pipe_read_fd, buff, sizeof(buff) - 1);

	// Case 1: Got data - accumulate and continue
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffs[client_fd] += std::string(buff, bytes_read);
		return;
	}
	if (bytes_read < 0)
	{
		return;
	}

	// Get accumulated output
	std::string	cgiOutput = _cgiBuffs[client_fd];
	_cgiBuffs.erase(client_fd);

	// Close pipe and clean up
	close(pipe_read_fd);
	_removePipeFromPoll(pipe_read_fd);
	_pipeToClientMap.erase(pipe_read_fd);
	_cgiBytesWritten.erase(pipe_read_fd);
	_cgiStartTime.erase(client_fd);

	// Decrement active CGI counter
	if (_active_cgis > 0)
		_active_cgis--;

	server.cleanupCgi(client_fd);

	// Parse CGI output
	Response	response;
	size_t		headerEnd = cgiOutput.find("\r\n\r\n");

	if (headerEnd != std::string::npos)
	{
		// Case 1: Headers + body
		std::string	headersPart = cgiOutput.substr(0, headerEnd);
		std::string	bodyPart = cgiOutput.substr(headerEnd + 4);
		response.setBody(bodyPart);

		int			cgi_status_code = Http::OK;
		bool		has_content_type = false;
		bool		has_location = false;
		std::string	location_url;

		std::stringstream	header_ss(headersPart);
		std::string			line;

		while (std::getline(header_ss, line))
		{
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
					response.setHeader(key, value);
				}
			}
		}
		if (has_location && cgi_status_code == Http::OK)
			cgi_status_code = Http::FOUND;

		response.setStatus(cgi_status_code);

		if (!has_content_type && !has_location && !bodyPart.empty())
			response.setHeader("Content-Type", "text/html");

		if (has_location && (cgi_status_code == Http::FOUND ||
							 cgi_status_code == Http::MOVED_PERMANENTLY))
			bodyPart = "";

		response.setBody(bodyPart);
		response.setHeader("Content-Length", Utils::toStr(bodyPart.size()));
	}
	else if (!cgiOutput.empty())
	{
		// Case 2: No headers, just raw output
		response.setStatus(Http::OK);
		response.setBody(cgiOutput);
		response.setHeader("Content-Type", "text/html");
		response.setHeader("Content-Length", Utils::toStr(cgiOutput.size()));
	}
	else
	{
		// Case 3: Empty response
		response.setStatus(Http::NO_CONTENT);
		response.setBody("");
		response.setHeader("Content-Length", "0");
	}

	if (response.getStatus() == Http::NO_CONTENT ||
	   (response.getStatus() >= 300 && response.getStatus() < 400))
	{
		response.setBody("");
		response.setHeader("Content-Length", "0");
	}

	server.setCgiResponse(client_fd, response);

	// Switch target client socket back to POLLOUT
	for (size_t i = 0; i < _fds.size(); ++i)
	{
		if (_fds[i].fd == client_fd)
		{
			_fds[i].events = POLLOUT; // Wake up the client socket to send the answer
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
