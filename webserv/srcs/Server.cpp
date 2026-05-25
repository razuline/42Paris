/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 19:06:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Server::Server(const Config &config) :
	_serv_fd(-1),
	_port(config.getPort()),
	_config(config)
{
	memset(&_addr, 0, sizeof(_addr));
}

Server::Server(const Server &copy) :
	_serv_fd(-1),
	_port(copy._port),
	_config(copy._config)
{
	memset(&_addr, 0, sizeof(_addr));
}

// Private
Server
&Server::operator=(const Server &other)
{
	if (this != &other)
	{
		_port = other._port;
		_config = other._config;
	}
	return *this;
}

Server::~Server()
{
	// Close main listening socket if open
	if (_serv_fd != -1)
		close(_serv_fd);

	// Clean up any remaining active clients
	std::map<int, Request>::iterator	it = _reqs.begin();
	while (it != _reqs.end())
	{
		close(it->first);
		_clearClientState(it->first);
		_reqs.erase(it++);
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Server::_clearClientState(int client_fd)
{
	// Erase data structures mapped to this client to prevent memory/state leaks
	_reqs.erase(client_fd);
	_resps.erase(client_fd);
	_cgis.erase(client_fd);
}

std::string
Server::_readFile(const std::string &path)
{
	std::ifstream		file(path.c_str());
	std::stringstream	buff;

	if (!file.is_open())
		return "";
	buff << file.rdbuf();
	return buff.str();
}

/* --------------------------- CORE SOCKET METHODS -------------------------- */

void
Server::setup()
{
	// 1. Create IPv4 TCP Socket
	_serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serv_fd < 0)
	{
		perror("Socket creation failed");
		return;
	}

	// 2. Allow immediate local port reuse
	//    Prevents "Address already in use" errors
	int	opt = 1;
	if (setsockopt(_serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("Setsockopt REUSEADDR failed");
		return;
	}

	// 3. Configure Socket Address Structure
	_addr.sin_family = AF_INET;         // IPv4 addresses
	_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
	_addr.sin_port = htons(_port);      // Convert port to Network Byte Order

	// 4. Bind socket to the specified port
	if (bind(_serv_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		perror("Bind failed");
		return;
	}

	// 5. Switch listening socket to non-blocking mode
	if (fcntl(_serv_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("Fcntl non-block failed");
		return;
	}

	// 6. Start listening with a standard connection backlog queue
	if (listen(_serv_fd, 128) < 0)
	{
		perror("Listen failed");
		return;
	}
}

int
Server::getServerFd() const
{
	return _serv_fd;
}

/* ----------------------- NON-BLOCKING I/O HANDLERS ------------------------ */

int
Server::handleRead(int client_fd)
{
	char	buff[4096];

	// 1. Read raw bytes from the client socket without blocking
	int		bytes_read = recv(client_fd, buff, sizeof(buff) - 1, 0);
	if (bytes_read <= 0)
	{
		_reqs.erase(client_fd); // Connection dropped or error occurred
		return bytes_read;
	}
	buff[bytes_read] = '\0';

	// 2. Push network data chunk into the client's dedicated Request state machine
	_reqs[client_fd].addData(buff);

	// 3. Monitor if the HTTP parsing framework reached the COMPLETE stage
	if (_reqs[client_fd].isComplete())
	{
		// Extract the requested script path or URI from the completed Request
		std::string	path = _reqs[client_fd].getPath();

		// Simple check: does the URI target a CGI script? (e.g., ends with ".py")
		if (path.size() >= 3 && path.substr(path.size() - 3) == ".py")
		{
			int		cgi_status = _cgis[client_fd].execute(_reqs[client_fd], path);

			if (cgi_status == 500)
			{
				return 2; // Switch to POLLOUT to send the error page
			}
			return 3; // CUSTOM SIGNAL: Tell Cluster to monitor CGI pipes now
		}
	}
	else
	{
		// Standard Static Request (HTML, CSS, Images, etc.)
		Response	response;

		_resps[client_fd] = response;

		return 2; // Standard Signal: Switch client from POLLIN to POLLOUT
	}
	return 1; // Incomplete, keep reading data on POLLIN
}

int
Server::handleWrite(int client_fd)
{
	// 1. Fetch the completely rendered HTTP response raw string
	std::string	res_str = _resps[client_fd].build();

	// 2. Transmit the chunk through the client socket without blocking
	int			bytes_sent = send(client_fd, res_str.c_str(), res_str.size(), 0);

	if (bytes_sent <= 0)
	{
		_clearClientState(client_fd);
		return bytes_sent;
	}
	_clearClientState(client_fd);

	return 2; // Signal Cluster that sending is complete
}

// int	setsockopt(int sockfd, int level, int optname,
// 					const void *optval, socklen_t optlen);
// int	accept(int, sockaddr *, socklen_t *);