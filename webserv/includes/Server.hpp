/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/27 16:39:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Config.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Location.hpp"
# include "CGI.hpp"
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
# include <map>

extern volatile sig_atomic_t	g_stop;

class Server
{
private:
	int							_serv_fd; // Main listening socket
	int							_port;    // Port number from config
	struct sockaddr_in			_addr;    // Socket address structure
	Config						_config;  // Configuration module

	// Multiplexing data structures mapping client sockets to HTTP states
	std::map<int, Request>		_reqs;    // client_fd -> Request state machine
	std::map<int, Response>		_resps;   // client_fd -> Response frame
	std::map<int, CGI *>		_cgis;    // client_fd -> Active CGI trackers

	/* --- Private Internal Helpers --- */
	std::string		_readFile(const std::string &path);
	void			_clearClientState(int client_fd);
	const Location	*_matchLocation(const std::string &path) const;

	// Hidden assignment operator
	Server			&operator=(const Server &other);

public:
	/* --- Orthodox Canonical Form --- */
	Server(const Config &config);
	Server(const Server &copy);
	~Server();

	/* --- Core Socket Methods --- */
	void	setup();

	/* --- Non-blocking I/O Handlers --- */
	// returns: <=0 error/disconn, 1 partial, 2 complete
	int		handleRead(int client_fd);
	int		handleWrite(int client_fd);

	/* --- Getters --- */
	int		getServerFd() const;
	int		getReadFd(int client_fd);  // To read from Python
	int		getWriteFd(int client_fd); // To write to Python
};

#endif

// socket(domain, type, protocol);