/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/01 17:29:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Config.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Utils.hpp"

# include <csignal>
# include <cstdio>
# include <cstring>
# include <fcntl.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <vector>
# include <sys/poll.h>
# include <fstream>
# include <sstream>
# include <iostream>
# include <unistd.h>

// Global flag to control the server's main loop
// 'extern' means it's defined in another file (main.cpp)
extern volatile sig_atomic_t	g_stop;

class Server
{
private:
	int					_serv_fd; // Server's main listening socket descriptor
	int					_port;    // Port number the server listens on
	struct sockaddr_in	_addr;    // Server's address information structure

	std::vector<struct pollfd>	_fds;
	std::map<int, Request>		_reqs;

	Config				_config;

	/* --- Private Internal Helpers --- */
	void		_addToPoll(int fd);
	void		_acceptNewConnection();
	void		_removeClient(int idx);
	void		_handleClientRequest(int idx);
	std::string	_readFile(const std::string &path);

	void		_executeRequest(int fd, Request &req);
	void		_handleDisconnection(int idx);

	// Prevent copying to avoid issues with shared file descriptors
	Server	&operator=(const Server &other);

public:
	/* --- Orthodox Canonical Form --- */
	Server(const Config &config);
	Server(const Server &copy);
	~Server();

	/* --- Core Methods --- */
	void	setup(); // Initialises socket, bind, and listen
	void	run();   // Main execution loop to accept connections

	/* --- Getters --- */
	int		getFd() const; // Returns the server's main listening socket
};

// Signal handler prototype
void	handle_signal(int sig);

#endif

// socket(domain, type, protocol);