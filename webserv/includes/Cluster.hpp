/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:51:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 14:14:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include <vector>
# include <map>
# include <sys/poll.h>
# include <unistd.h>
# include <fcntl.h>
# include <iostream>

# include "Server.hpp"

class Cluster
{
private:
	std::map<int, Server *>		_servers;               // serv_fd -> Server*
	std::map<int, Server *>		_clients;               // client_fd -> Server*
	std::vector<struct pollfd>	_fds;                   // poll array

	/* --- Copy Blockade --- */
	Cluster(const Cluster &copy);
	Cluster	&operator=(const Cluster &other);

	/* --- Private Internal Helpers --- */
	void	_addNewConnection(int serv_fd);             // accept()
	void	_handleClientRead(int fd, Server &server);  // recv()
	void	_handleClientWrite(int fd, Server &server); // send()
	void	_closeConnection(int fd);                   // close() & clear
	void	_handleCGIWrite(int pipe_write_fd, Server &server);
	void	_handleCGIRead(int pipe_read_fd, Server &server);

public:
	/* --- Orthodox Canonical Form --- */
	Cluster();
	~Cluster();

	/* --- Core Methods --- */
	void	setup(std::vector<Config> configs);
	void	run();
};

#endif