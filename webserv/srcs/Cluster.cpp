/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/24 17:06:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Cluster::Cluster()
{
	// std::cout << "Default constructor called" << std::endl;
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

	// std::cout << "Destructor called" << std::endl;
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
		// Request's complete. Switch from POLLIN to POLLOUT to look for write readiness
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			if (_fds[i].fd == fd)
			{
				_fds[i].events = POLLOUT;
				break;
			}
		}
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
	std::cout << "[Cluster] Connection closed on fd " << fd << std::endl;
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Cluster::setup(std::vector<Config> configs)
{
	for (size_t i = 0; i < configs.size(); ++i)
	{
		Server	*server = new Server(configs[i]);
		server->setup(); // Opens, binds, and listens the server socket

		int	serv_fd = server->getFd();
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
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			// Handle reading and new connections
			if (_fds[i].revents & POLLIN)
			{
				if (_servers.count(_fds[i].fd))
					_addNewConnection(_fds[i].fd);
				else if (_clients.count(_fds[i].fd))
					_handleClientRead(_fds[i].fd, *_clients[_fds[i].fd]);
			}
			// Handle writing responses
			else if (_fds[i].revents & POLLOUT)
			{
				if (_clients.count(_fds[i].fd))
					_handleClientWrite(_fds[i].fd, *_clients[_fds[i].fd]);
			}
			// Handle errors or sudden disconnections
			else if (_fds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
				_closeConnection(_fds[i].fd);
		}
	}
}
