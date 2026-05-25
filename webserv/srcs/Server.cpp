/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 20:14:09 by erazumov         ###   ########.fr       */
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

	// Safe iteration to clear remaining active connections and states
	std::map<int, Request>::iterator	it = _reqs.begin();
	while (it != _reqs.end())
	{
		int	client_fd = it->first;

		it++;

		close(client_fd);
		_clearClientState(it->first);
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Server::_clearClientState(int client_fd)
{
	// Erase data structures mapped to this client to prevent memory/state leaks
	_reqs.erase(client_fd);
	_resps.erase(client_fd);

	// If a CGI instance was dynamically allocated for this client, delete it safely
	std::map<int, CGI*>::iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		delete it->second; // Triggers CGI's destructor, closing its pipes
		_cgis.erase(it);
	}
}

std::string
Server::_readFile(const std::string &path)
{
	std::ifstream		file(path.c_str());
	if (!file.is_open())
		return "";

	std::stringstream	buff;
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

	// 2. Switch listening socket to non-blocking mode
	if (fcntl(_serv_fd, F_SETFL, O_NONBLOCK) < 0)
		perror("Fcntl non-block setup failed");

	// 3. Allow immediate local port reuse
	//    Prevents "Address already in use" errors
	int	opt = 1;
	if (setsockopt(_serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		perror("Setsockopt REUSEADDR failed");

	// 4. Configure Socket Address Structure
	_addr.sin_family = AF_INET;         // IPv4 addresses
	_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
	_addr.sin_port = htons(_port);      // Convert port to Network Byte Order

	// 5. Bind socket to the specified port
	if (bind(_serv_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		perror("Bind failed");
		return;
	}

	// 6. Start listening with a standard connection backlog queue
	if (listen(_serv_fd, 128) < 0)
	{
		perror("Listen failed");
		return;
	}
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
		_clearClientState(client_fd); // Connection dropped or error occurred
		return bytes_read;
	}
	buff[bytes_read] = '\0';

	// 2. Push network data chunk into the client's dedicated Request state machine
	_reqs[client_fd].setLimit(_config.getClientMaxBodySize());
	_reqs[client_fd].addData(std::string(buff, bytes_read));

	if (_reqs[client_fd].getState() == Request::ERROR)
	{
		Response	res;
		res.defaultErrorPage(413); // Payload Too Large
		_resps[client_fd] = res;
		return 2; // Switch to write out error
	}

	// 3. Monitor if the HTTP parsing framework reached the COMPLETE stage
	if (_reqs[client_fd].isComplete())
	{
		std::string	path = _reqs[client_fd].getPath();
		if (path == "/")
			path = _config.getHomePage();

		std::string	fullPath = _config.getFolderRoot() + "/" + (path[0] == '/' ? path.substr(1) : path);

		// CASE A: Check if target file requires CGI processing (e.g., Python script)
		if (path.size() >= 3 && path.substr(path.size() - 3) == ".py")
		{
			_cgis[client_fd] = new CGI();
			int	cgi_status = _cgis[client_fd]->execute(_reqs[client_fd], fullPath);

			if (cgi_status == 500)
			{
				delete _cgis[client_fd];
				_cgis.erase(client_fd);

				Response	res;
				res.defaultErrorPage(500);
				_resps[client_fd] = res;
				return 2; // Switch to POLLOUT to send the error page
			}
			return 3; // Tell Cluster to monitor CGI pipes instead of client socket
		}
		// CASE B: Standard static resource management (HTML, CSS, Images, etc.)
		else
		{
			Response	response;
			// Use fullPath to read static files later
			_resps[client_fd] = response;

			return 2; // Standard Signal: Switch client from POLLIN to POLLOUT
		}
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

	return 0; // Complete transaction closure
}

/* -------------------------------- GETTERS --------------------------------- */

int
Server::getServerFd() const
{
	return _serv_fd;
}

int
Server::getReadFd(int client_fd)
{
	return _cgis[client_fd]->getReadFd();
}

int
Server::getWriteFd(int client_fd)
{
	return _cgis[client_fd]->getWriteFd();
}
