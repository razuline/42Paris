/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/12 18:27:48 by erazumov         ###   ########.fr       */
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
# include <fstream>
# include <iostream>
# include <map>
# include <netinet/in.h>
# include <sstream>
# include <sys/socket.h>
# include <sys/stat.h>
# include <sys/poll.h>
# include <sys/types.h>
# include <unistd.h>
# include <vector>

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

	static int					_active_cgis; // Track active CGI processes
	static const int			MAX_CONCURRENT_CGIS = 100; // Limit concurrent CGIs

	/* --- Private Internal Helpers --- */
	std::string			_readFile(const std::string &path);
	const Location		*_matchLocation(const std::string &path) const;

	/* --- Split Handlers for handleRead --- */
	ReadStatus			_execCompetedOrder(int client_fd, Request &req);
	bool				_checkIncMethod(const Location *loc, const std::string &method) const;
	bool				_isCgiResource(const Location *loc, const std::string &method,
									   const std::string &path) const;

	ReadStatus			_runStaticGet(int client_fd, std::string fullPath);
	ReadStatus			_runStaticHead(int client_fd, std::string fullPath);
	ReadStatus			_runStaticPostUpload(int client_fd, std::string fullPath);
	ReadStatus			_runStaticDeleteFile(int client_fd, std::string fullPath);
	ReadStatus			_runDirRedirect(int client_fd, const std::string &reqPath);

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

	ReadStatus			clearClientState(int client_fd);
	void				cleanupCgi(int client_fd);

	/* --- Setters / Getters --- */
	void				setCgiResponse(int client_fd, const Response &res);
	int					getServerFd() const;
	int					getReadFd(int client_fd);  // To read from Python
	int					getWriteFd(int client_fd); // To write to Python
	const std::string	&getRequestBody(int client_fd);
	int					getActiveCgis();
	void				setActiveCgis(int count);
};

#endif

// socket(domain, type, protocol);