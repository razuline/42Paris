/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:51:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/01 17:42:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include <vector>
# include <map>
# include <poll.h>
# include <unistd.h>
# include <fcntl.h>
# include <iostream>

# include "Server.hpp"

class Cluster
{
private:
	std::map<int, Server *>		_servers;
	std::map<int, Server *>		_fd_to_server;
	std::vector<struct pollfd>	_pollfds;

	/* --- Private Internal Helpers --- */
	void	_addNewConnection(int serv_fd);
	void	_handleClient(int fd, Server &server);
	void	_closeConnection(int fd);

public:
	/* --- Orthodox Canonical Form --- */
	Cluster();
	Cluster(const Cluster &copy);
	Cluster &operator=(const Cluster &other);
	~Cluster();

	/* --- Core Methods --- */
	void	setup(std::vector<Config> configs); // Initialise all virtual servers
	void	run(); // The main infinite loop
};

#endif