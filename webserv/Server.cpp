/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/25 17:06:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Request.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Server::Server(int port) :
	_serv_fd(-1),
	_port(port)
{
	// Zero out the address structure to prevent memory garbage issues
	memset(&_addr, 0, sizeof(_addr));

	// std::cout << "Default constructor called" << std::endl;
}

Server::Server(const Server &copy) :
	_serv_fd(-1),
	_port(copy._port)
{
	// Copy the address structure and port, but don't share the socket FD
	memset(&_addr, 0, sizeof(_addr));

	// std::cout << "Copy constructor called" << std::endl;
}

// Private
Server
&Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->_port = other._port;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

Server::~Server()
{
	// Ensure the socket is closed when the object is destroyed
	if (_serv_fd != -1)
	{
		close(_serv_fd);
	}

	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- HELPER METHODS ----------------------------- */

void
Server::addToPoll(int fd)
{
	// Initialising the server socket for polling
	struct pollfd	serv_pfd;

	serv_pfd.fd = _serv_fd;
	serv_pfd.events = POLLIN; // Monitor for incoming connections
	serv_pfd.revents = 0;

	_fds.push_back(serv_pfd);
}

void
Server::acceptNewConnection()
{
	struct sockaddr_in	addr;
	// Reset the size of the structure before each accept call
	socklen_t			size = sizeof(addr);

	// 1. Accept the incoming connection from the server socket
	int					new_fd = accept(_serv_fd, (struct sockaddr *)&addr, &size);

	if (new_fd >= 0)
	{
		// 2. MANDATORY: Set the socket to non-blocking mode (Rule IV.2)
		// This prevents the server from hanging during I/O operations
		fcntl(new_fd, F_SETFL, O_NONBLOCK);

		// 3. Add this new client to the list of monitored descriptors
		addToPoll(new_fd);

		std::cout << "New client connected on fd " << new_fd << std::endl;
	}
	else
	{
		// If accept fails, we just log the error
		perror("Accept failed");
	}
}

void
Server::removeClient(int idx)
{
	std::cout << "Client on fd " << _fds[idx].fd << " disconnected." << std::endl;

	// RECV ERROR: Handle unexpected disconnection or read failure
	close(_fds[idx].fd);
	_fds.erase(_fds.begin() + idx);
}

void
Server::handleClientRequest(int idx)
{
	char	buff[4096];
	std::memset(buff, 0, sizeof(buff));

	// 1. Read data from the client (using the fd at index i)
	ssize_t	bytes_received = recv(_fds[idx].fd, buff, sizeof(buff) - 1, 0);

	if (bytes_received > 0)
	{
		// 2. TRANSLATION: Use the Request class to understand the buffer
		Request	req;
		req.parse(std::string(buff));

		// What the browser wants in the terminal
		std::cout << "Client (fd " << _fds[idx].fd << ") wants: "
				  << req.getMethod() << " " << req.getPath() << std::endl;

		// 3. ANSWER: Send a simple "OK" back
		const char	*resp = "HTTP/1.1 200 OK\r\nContent-Length: 11\r\n\r\nHello 42!\n";
		send(_fds[idx].fd, resp, std::strlen(resp), 0);
	}
	else if (bytes_received == 0)
	{
		// CLIENT LEFT: The browser closed the connection
		std::cout << "Client on fd " << _fds[idx].fd << " disconnected." << std::endl;
		removeClient(idx);
	}
	else
	{
		// ERROR: Something went wrong with the connection
		perror("Recv failed");
		removeClient(idx);
	}
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Server::setup()
{
	// 1. Create the master socket (IPv4, TCP protocol)
	_serv_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serv_fd < 0)
	{
		perror("Socket creation failed");
		return;
	}

	// Set the socket to non-blocking mode
	if (fcntl(_serv_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		perror("fcntl failed");
	}

	// 2. Set socket options to allow immediate port reuse after restart
	int	opt = 1;
	if (setsockopt(_serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("Setsockopt failed");
		// We can continue, but port might be busy for a while after restart
	}

	// 3. Configure the server's address structure
	_addr.sin_family = AF_INET;         // IPv4 addresses
	_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all available network interfaces
	_addr.sin_port = htons(_port);      // Convert port to network byte order (Big-Endian)

	// 4. Bind the socket to the port and address
	if (bind(_serv_fd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
	{
		perror("Bind failed (port might be in use)");
		return;
	}

	// 5. Put the socket into listening mode to wait for incoming connections
	// 128 is the max number of connections waiting in the queue
	if (listen(_serv_fd, 128) < 0)
	{
		perror("Listen failed");
		return;
	}
}

void
Server::run()
{
	// 1. Add server socket to poll list
	addToPoll(_serv_fd);

	std::cout << "Server is listening on port " << _port << "..." << std::endl;

	while (g_stop == 0)
	{
		// 2. Wait for activity on any socket (requirement)
		// Using -1 makes poll block indefinitely until an event occurs
		if (poll(&_fds[0], _fds.size(), -1) < 0)
		{
			if (g_stop == 0)
				perror("poll error");
			continue;
		}

		// Iterate through the vector of file descriptors to check for events
		for (size_t i = 0; i < _fds.size(); ++i)
		{
			// Check if the descriptor is ready for reading
			if (_fds[i].revents & POLLIN)
			{
				if (_fds[i].fd == _serv_fd)
					acceptNewConnection();  // New guest arrived
				else
					handleClientRequest(i); // Existing guest sent data
			}
		}
	}
}

// int	setsockopt(int sockfd, int level, int optname,
// 					const void *optval, socklen_t optlen);
// int	accept(int, sockaddr *, socklen_t *);