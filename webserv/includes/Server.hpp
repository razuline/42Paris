/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 17:13:38 by erazumov         ###   ########.fr       */
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
	std::vector<struct pollfd>	_fds;
	std::map<int, Request>		_reqs;  // client_fd -> Request
	std::map<int, Response>		_resps; // client_fd -> Response



	/* --- Private Internal Helpers --- */
	void		_addToPoll(int fd);
	void		_acceptNewConnection();
	void		_removeClient(int idx);
	void		_handleClientRequest(int idx);
	std::string	_readFile(const std::string &path);

	void		_executeRequest(int fd, Request &req);
	void		_handleDisconnection(int idx);

	// Prevent copying to avoid issues with shared file descriptors
	Server		&operator=(const Server &other);

public:
	/* --- Orthodox Canonical Form --- */
	Server(const Config &config);
	Server(const Server &copy);
	~Server();

	/* --- Core Methods --- */
	void	setup(); // Initialises socket, bind, and listen

	// returns: <=0 error/disconn, 1 partial, 2 complete
	int		handleRead(int client_fd);
	int		handleWrite(int client_fd);

	/* --- Getters --- */
	int		getFd() const; // Returns the server's main listening socket
};

// Signal handler prototype
void	handle_signal(int sig);

#endif

// socket(domain, type, protocol);