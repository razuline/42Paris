/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cluster.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 16:51:10 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/14 21:32:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLUSTER_HPP
# define CLUSTER_HPP

# include "Server.hpp"
# include "Config.hpp"
# include "HttpStatus.hpp"

# include <iostream>
# include <fcntl.h>
# include <map>
# include <sys/poll.h>
# include <sys/wait.h>
# include <unistd.h>
# include <vector>

class Cluster
{
private:
	std::map<int, Server *>		_servers;               // serv_fd -> Server*
	std::map<int, Server *>		_clients;               // client_fd -> Server*
	std::vector<struct pollfd>	_fds;                   // poll array

	/* --- Asynchronous CGI Trackers --- */
	std::map<int, int>			_pipeToClientMap;       // Maps pipe_read_fd -> client_fd
	std::map<int, std::string>	_cgiBuffs;              // Maps client_fd -> accumulated response
	std::map<int, size_t>		_cgiBytesWritten;
	std::map<int, time_t>		_cgiStartTime;          // Track when CGI started
	std::map<int, int>			_pendingCgiReadFd;  // client_fd -> read_fd

	int							_active_cgis;

	/* --- Private Internal Helpers --- */
	void	_addNewConnection(int serv_fd);             // accept()
	void	_handleClientRead(int fd, Server &server);  // recv()
	void	_handleClientWrite(int fd, Server &server); // send()
	void	_closeConnection(int fd);                   // close() & clear
	void	_handleCGIWrite(int pipe_write_fd, Server &server);
	void	_handleCGIRead(int pipe_read_fd, Server &server);
	void	_removePipeFromPoll(int pipe_fd);

	/* --- Copy Blockade --- */
	Cluster(const Cluster &copy);
	Cluster	&operator=(const Cluster &other);

public:
	/* --- Orthodox Canonical Form --- */
	Cluster();
	~Cluster();

	/* --- Core Methods --- */
	void	setup(std::vector<Config> configs);
	void	run();
};

#endif