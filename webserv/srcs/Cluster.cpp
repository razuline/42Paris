/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 17:16:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/01 17:44:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cluster.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Cluster::Cluster()
{
	// std::cout << "Default constructor called" << std::endl;
}

Cluster::Cluster(const Cluster &copy)
{
	*this = copy;

	// std::cout << "Copy constructor called" << std::endl;
}

Cluster
&Cluster::operator=(const Cluster &other)
{
	if (this != &other)
	{
		this->_servers = other._servers;
		this->_fd_to_server = other._fd_to_server;
		this->_pollfds = other._pollfds;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

Cluster::~Cluster()
{
	// Ensure all file descriptors are closed when the cluster is destroyed
	std::map<int, Server *>::iterator	it;

	for (it = _servers.begin(); it != _servers.end(); ++it)
	{
		delete it->second; // Free each server
	}

	// std::cout << "Destructor called" << std::endl;
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

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

		std::cout << "[Cluster] Server ready on port "
					<< configs[i].getPort() << std::endl;
	}
}