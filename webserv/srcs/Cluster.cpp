/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/23 23:33:26 by erazumov         ###   ########.fr       */
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
	// Expected return: <= 0 for error/disconnect,
	//                  1 for partial data,
	//                  2 for request complete
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
		Server	*newServ = new Server(configs[i]);
		newServ->setup(); // Opens the socket, binds and listens

		int	servFd = newServ->getFd();
		_servers[servFd] = newServ;

		// Add the server listening socket to our monitoring list
		struct pollfd	pfd;
		pfd.fd = servFd;
		pfd.events = POLLIN; // Look for new incoming connections
		pfd.revents = 0;
		_pollfds.push_back(pfd);

		_fd_to_server[servFd] = newServ;

		std::cout << "[Cluster] Server ready on port "
					<< configs[i].getPort() << std::endl;
	}
}

void
Cluster::run()
{
	while (g_stop == 0)
	{
		// 2. Wait for activity on any socket (requirement)
		// Using -1 makes poll block indefinitely until an event occurs
		if (poll(&_pollfds[0], _pollfds.size(), -1) < 0)
		{
			if (g_stop == 0)
				perror("poll error");
			continue;
		}
		// Iterate through the vector of file descriptors to check for events
		for (size_t i = 0; i < _pollfds.size(); ++i)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				int	curr_fd = _pollfds[i].fd;

				if (_servers.find(curr_fd) != _servers.end())
					_addNewConnection(curr_fd);
				else
				{
					size_t	before = _pollfds.size();
					Server	*client_serv = _fd_to_server[curr_fd];

					_handleClient(curr_fd, *client_serv);

					if (_pollfds.size() < before)
						i--;
				}
			}
		}
	}
}
