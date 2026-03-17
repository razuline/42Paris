/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/17 17:18:05 by erazumov         ###   ########.fr       */
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
	// Reset the size of the structure before each accept call
	socklen_t			addrSize = sizeof(clientAddr);

	// Initialising the server socket for polling
	struct pollfd	serv_pfd;

	serv_pfd.fd = _serv_fd;
	serv_pfd.events = POLLIN; // Monitor for incoming connections
	serv_pfd.revents = 0;
	_fds.push_back(serv_pfd);

	std::cout << "Server is listening on port " << _port << "..." << std::endl;

	while(g_stop == 0)
	{
		// Wait for events on any monitored file descriptor
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
				{
					// HANDLE NEW CONNECTION: The server socket has a pending connection
					int	new_fd = accept(_serv_fd, (struct sockaddr *)&clientAddr,
									&addrSize);
					if (new_fd >= 0)
					{
						// Set the new client socket to non-blocking mode
						fcntl(new_fd, F_SETFL, O_NONBLOCK);

						struct pollfd	client_pfd;
						client_pfd.fd = new_fd;
						client_pfd.events = POLLIN; // Wait for the client to send data
						client_pfd.revents = 0;
						_fds.push_back(client_pfd);
						std::cout << "New client connected on fd " << new_fd
								  << std::endl;
					}
				}
				else
				{
					// HANDLE EXISTING CLIENT: An established connection has sent data
					char	buff[4096];
					std::memset(buff, 0, sizeof(buff));

					// Receive data from the client socket
					ssize_t	bytes_read = recv(_fds[i].fd, buff,
											sizeof(buff) - 1, 0);

					if (bytes_read > 0)
					{
						// Process the request and send a basic HTTP response
						std::cout << "Request from fd " << _fds[i].fd << ":\n"
								  << buff << std::endl;

						const char	*response =
							"HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello World!\n";
						send(_fds[i].fd, response, std::strlen(response), 0);

						// Note: Connection is kept open for potential further requests (Keep-Alive)
					}
					else if (bytes_read == 0)
					{
						// CLIENT DISCONNECTED: The peer has closed the connection
						std::cout << "Client on fd " << _fds[i].fd
								  << " disconnected." << std::endl;
						close(_fds[i].fd);
						_fds.erase(_fds.begin() + i);
						--i; // Adjust index after removing element from vector
					}
					else
					{
						// RECV ERROR: Handle unexpected disconnection or read failure
						perror("recv error");
						close(_fds[i].fd);
						_fds.erase(_fds.begin() + i);
						--i;
					}
				}
			}
			// Clear revents after processing the event for this descriptor
			_fds[i].revents = 0;
		}
	}
}

// int	setsockopt(int sockfd, int level, int optname,
// 					const void *optval, socklen_t optlen);
// int	accept(int, sockaddr *, socklen_t *);