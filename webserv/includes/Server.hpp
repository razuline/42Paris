/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 19:06:05 by erazumov         ###   ########.fr       */
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
	struct sockaddr_in			_addr;    // Address structure
	Config						_config;  // Configuration instance

	// Multiplexing data structures mapping client sockets to their HTTP state
	std::map<int, Request>		_reqs;    // client_fd -> Request obj
	std::map<int, Response>		_resps;   // client_fd -> Response obj
	std::map<int, CGI>			_cgis;    // client_fd -> CGI tracker

	/* --- Private Internal Helpers --- */
	std::string	_readFile(const std::string &path);
	void		_clearClientState(int client_fd);

	// Disallow assignment operator
	Server		&operator=(const Server &other);

public:
	/* --- Orthodox Canonical Form --- */
	Server(const Config &config);
	Server(const Server &copy);
	~Server();

	/* --- Core Socket Methods --- */
	void	setup();
	int		getServerFd() const;

	/* --- Non-blocking I/O Handlers --- */
	// returns: <=0 error/disconn, 1 partial, 2 complete
	int		handleRead(int client_fd);
	int		handleWrite(int client_fd);
};

#endif

// socket(domain, type, protocol);