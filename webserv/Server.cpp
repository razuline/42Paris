/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/09 17:31:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
	struct sockaddr_in	clientAddr;
	socklen_t			addrSize;

	std::cout << "Server is listening on port " << _port << "..." << std::endl;

	// The loop continues until a SIGINT (Ctrl+C) is received
	while(g_stop == 0)
	{
		// Reset the size of the structure before each accept call
		addrSize = sizeof(clientAddr);

		// Accept a new incoming connection
		// This call blocks execution until a client connects
		int	client_fd = accept(_serv_fd, (struct sockaddr *)&clientAddr, &addrSize);

		if (client_fd >= 0)
		{
			std::cout << "Сonnection accepted!" << std::endl;

			// Simple HTTP response to acknowledge the connection
			const char	*msg =
				"HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello World!\n";
			send(client_fd, msg, strlen(msg), 0);

			// Close the communication socket with the client
			close(client_fd);
		}
		else
		{
			// In non-blocking mode, if there's no client, accept sets errno to EAGAIN
			if (errno != EAGAIN && errno != EWOULDBLOCK)
			{
				if (g_stop == 0)
				{
					perror("Accept failed");
				}
			}
		}
		// Avoid 100% CPU usage
		usleep(1000); // 1ms
	}
}

// int	setsockopt(int sockfd, int level, int optname,
// 					const void *optval, socklen_t optlen);
// int	accept(int, sockaddr *, socklen_t *);