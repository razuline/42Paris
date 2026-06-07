/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/07 14:38:29 by erazumov         ###   ########.fr       */
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
# include "HttpStatus.hpp"

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
public:
	enum ReadStatus
	{
		READ_ERROR = 0,                       // Error or disconnect (<= 0)
		READ_INCOMPLETE = 1,                  // Incompete request, keep reading
		STATIC_READY = 2,                     // Static file ready for POLLOUT
		CGI_READY = 3                         // CGI script ready to execute
	};

	enum WriteStatus
	{
		WRITE_ERROR = 0,
		WRITE_INCOMPLETE = 1,
		WRITE_COMPLETE = 2
	};

private:
	int							_serv_fd;    // Main listening socket
	int							_port;       // Port number from config
	struct sockaddr_in			_addr;       // Socket address structure
	Config						_config;     // Configuration module

	// Multiplexing data structures mapping client sockets to HTTP states
	std::map<int, Request>		_reqs;       // client_fd -> Request state machine
	std::map<int, Response>		_resps;      // client_fd -> Response frame
	std::map<int, CGI *>		_cgis;       // client_fd -> Active CGI trackers
	std::map<int, std::string>	_writeBuffs; // client_fd -> Raw unsent response bytes

	/* --- Private Internal Helpers --- */
	std::string			_readFile(const std::string &path);
	void				_clearClientState(int client_fd);
	const Location		*_matchLocation(const std::string &path) const;

	// Hidden assignment operator
	Server				&operator=(const Server &other);

public:
	/* --- Orthodox Canonical Form --- */
	Server(const Config &config);
	Server(const Server &copy);
	~Server();

	/* --- Core Socket Methods --- */
	void				setup();

	/* --- Non-blocking I/O Handlers --- */
	// returns: <=0 error/disconn, 1 partial, 2 complete
	ReadStatus			handleRead(int client_fd);
	WriteStatus			handleWrite(int client_fd);

	void				clearClientState(int client_fd);

	/* --- Getters --- */
	int					getServerFd() const;
	int					getReadFd(int client_fd);  // To read from Python
	int					getWriteFd(int client_fd); // To write to Python
	std::string			getRequestBody(int client_fd);
	void				setCgiResponse(int client_fd, const Response &res);
};

#endif

// socket(domain, type, protocol);