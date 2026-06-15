/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/15 14:40:06 by erazumov         ###   ########.fr       */
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
		ss << "[Cluster] Server virtual host listening on port ["
		   << configs[i].getPort() << "]";
		Utils::logInfo(ss.str());
	}
}

void
Cluster::run()
{
	while (g_stop == 0)
	{
		// 1. NON-BLOCKING PROCESS REAPER
		while (waitpid(-1, NULL, WNOHANG) > 0);

		// 2. TIMEOUT METRONOME (1 second)
		int	ret = poll(&_fds[0], _fds.size(), 1000);
		if (ret < 0)
		{
			if (g_stop == 0)
				perror("poll error");
			continue;
		}

		// 3. LIVE HEARTBEAT PULSE
		if (ret == 0)
		{
			Utils::logHeartbeat();
			continue;
		}

		// Check for CGI timeouts
		time_t	now = time(NULL);
		std::map<int, time_t>::iterator	it = _cgiStartTime.begin();
		while (it != _cgiStartTime.end())
		{
			if (now - it->second > 300)
			{
				std::stringstream	ss;
				ss << "CGI gate timeout triggered for client fd ["
				   << it->first << "]";
				Utils::logError(ss.str());

				if (_clients.count(it->first))
				{
					_clients[it->first]->cleanupCgi(it->first);

					Response	err_res;
					err_res.defaultErrorPage(Http::GATEWAY_TIMEOUT);
					_clients[it->first]->setCgiResponse(it->first, err_res);

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

		// Snapshot all fds that received an event
		std::vector<int>	ready_fds;
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].revents != 0)
				ready_fds.push_back(_fds[i].fd);
		}

		// Process each ready fd using live safe indices
		for (size_t k = 0; k < ready_fds.size(); ++k)
		{
			int	curr_fd = ready_fds[k];

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
				continue;

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
			else if ((revents & POLLOUT) && (events & POLLOUT) &&
					!(revents & (POLLERR | POLLHUP | POLLNVAL)))
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
					_closeConnection(curr_fd);
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

	std::stringstream	ss;
	ss << "[Cluster] New client connected on socket fd [" << client_fd << "]";
	Utils::logInfo(ss.str());
}

void
Cluster::_handleClientRead(int fd, Server &server)
{
	// Process non-blocking request reading stream
	Server::ReadStatus	status = server.handleRead(fd);

	if (status <= Server::READ_ERROR)
	{
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

		fcntl(cgi_write_fd, F_SETFL, O_NONBLOCK);
		fcntl(cgi_read_fd, F_SETFL, O_NONBLOCK);

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
	}
}

void
Cluster::_handleClientWrite(int fd, Server &server)
{
	pid_t	cgi_pid = server.getCgiPid(fd);
	if (cgi_pid > 0)
	{
		int	status;
		if (waitpid(cgi_pid, &status, WNOHANG) == 0)
			return;
	}

	// Inspect the exact transmission metrics returned by the non-blocking socket
	Server::WriteStatus	status = server.handleWrite(fd);

	if (status == Server::WRITE_ERROR)
	{
		_closeConnection(fd);
	}
	else if (status == Server::WRITE_COMPLETE)
	{
		std::stringstream	ss;
		ss << "[Cluster] Success response sent. Resetting client fd ["
		   << fd << "] back to POLLIN";
		Utils::logInfo(ss.str());

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

	std::stringstream	ss;
	ss << "[Cluster] Connection closed securely on fd [" << fd << "]";
	Utils::logInfo(ss.str());
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
	if (already_written >= body.size())
		return;

	size_t	remaining = body.size() - already_written;
	size_t	chunk_size = remaining > 65536 ? 65536 : remaining;

	int		ret = write(pipe_write_fd, body.c_str() + already_written, chunk_size);

	if (ret > 0)
	{
		_cgiBytesWritten[pipe_write_fd] += ret;
	}
	else
	{
		pid_t	cgi_pid = server.getCgiPid(client_fd);
		if (cgi_pid > 0)
		{
			int	status;
			if (waitpid(cgi_pid, &status, WNOHANG) > 0)
			{
				close(pipe_write_fd);
				_removePipeFromPoll(pipe_write_fd);
				_pipeToClientMap.erase(pipe_write_fd);
				_cgiBytesWritten.erase(pipe_write_fd);
			}
		}
		return;
	}
	if (_cgiBytesWritten[pipe_write_fd] == body.size())
	{
		close(pipe_write_fd);
		_removePipeFromPoll(pipe_write_fd);
		_pipeToClientMap.erase(pipe_write_fd);
		_cgiBytesWritten.erase(pipe_write_fd);
	}
}

void
Cluster::_handleCGIRead(int pipe_read_fd, Server &server)
{
	char	buff[65536];
	int		client_fd = _pipeToClientMap[pipe_read_fd];
	int		bytes_read = read(pipe_read_fd, buff, sizeof(buff) - 1);

	// Case 1: Accumulate data asynchronously
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		_cgiBuffs[client_fd].append(buff, bytes_read);
		return;
	}
	if (bytes_read < 0)
	{
		pid_t	cgi_pid = server.getCgiPid(client_fd);
		if (cgi_pid > 0)
		{
			int	status;
			if (waitpid(cgi_pid, &status, WNOHANG) == 0)
			{
				return;
			}
		}

		_cgiBuffs.erase(client_fd);
		close(pipe_read_fd);
		_removePipeFromPoll(pipe_read_fd);
		_pipeToClientMap.erase(pipe_read_fd);
		_cgiBytesWritten.erase(pipe_read_fd);
		_cgiStartTime.erase(client_fd);

		if (_active_cgis > 0)
			_active_cgis--;

		server.cleanupCgi(client_fd);

		Response	err_response;
		err_response.setStatus(Http::INTERNAL_SERVER_ERROR);
		err_response.setBody("");
		err_response.setHeader("Content-Length", "0");
		server.setCgiResponse(client_fd, err_response);

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

	// Case 2: EOF reached (bytes_read == 0)
	std::string	cgiOutput = _cgiBuffs[client_fd];
	_cgiBuffs.erase(client_fd);

	close(pipe_read_fd);
	_removePipeFromPoll(pipe_read_fd);
	_pipeToClientMap.erase(pipe_read_fd);
	_cgiBytesWritten.erase(pipe_read_fd);
	_cgiStartTime.erase(client_fd);

	if (_active_cgis > 0)
		_active_cgis--;

	server.cleanupCgi(client_fd);

	Response			response;
	std::stringstream	cgi_ss(cgiOutput);
	std::string			line;
	size_t				body_start_pos = 0;
	int					cgi_status_code = Http::OK;
	bool				has_content_type = false;
	bool				has_location = false;

	while (std::getline(cgi_ss, line))
	{
		body_start_pos += line.size() + 1;

		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);
		if (line.empty())
			break;

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

	std::string	bodyPart = "";
	if (body_start_pos < cgiOutput.size())
	{
		bodyPart = cgiOutput.substr(body_start_pos);
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

	server.setCgiResponse(client_fd, response);

	// Wake up the client socket for writing the payload back
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
