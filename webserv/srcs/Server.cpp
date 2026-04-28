/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/28 18:48:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Server::Server(const Config &config) :
	_serv_fd(-1),
	_port(config.getPort()),
	_config(config)
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
Server::_addToPoll(int fd)
{
	// Initialising the server socket for polling
	struct pollfd	pfd;

	pfd.fd = fd;
	pfd.events = POLLIN; // Monitor for incoming connections
	pfd.revents = 0;

	_fds.push_back(pfd);
}

void
Server::_acceptNewConnection()
{
	struct sockaddr_in	addr;
	std::memset(&addr, 0, sizeof(addr));

	// Reset the size of the structure before each accept call
	socklen_t	size = sizeof(addr);

	// 1. Accept the incoming connection from the server socket
	int			new_fd = accept(_serv_fd, (struct sockaddr *)&addr, &size);

	if (new_fd >= 0)
	{
		// 2. MANDATORY: Set the socket to non-blocking mode (Rule IV.2)
		// This prevents the server from hanging during I/O operations
		fcntl(new_fd, F_SETFL, O_NONBLOCK);

		// 3. Add this new client to the list of monitored descriptors
		_addToPoll(new_fd);

		std::cout << "New client connected on fd " << new_fd << std::endl;
	}
	else
	{
		// If accept fails, we just log the error
		perror("Accept failed");
	}
}

std::string
Server::_readFile(const std::string &fullPath)
{
	// 1. Open the file
	std::ifstream	file(fullPath.c_str());
	if (!file.is_open())
		return "";

	// 2. Read everything into a string
	std::stringstream	buff;
	buff << file.rdbuf();
	return buff.str();
}

void
Server::_removeClient(int idx)
{
	std::cout << "Client on fd " << _fds[idx].fd << " disconnected." << std::endl;

	// RECV ERROR: Handle unexpected disconnection or read failure
	close(_fds[idx].fd);
	_fds.erase(_fds.begin() + idx);
}

void
Server::_handleClientRequest(int idx)
{
	char	buff[4096];
	int		fd = _fds[idx].fd;

	// 1. Receive raw data from the client socket
	ssize_t	bytes = recv(fd, buff, sizeof(buff), 0);

	if (bytes > 0)
	{
		// 2. Set the body size limit from the server configuration
		_reqs[fd].setLimit(_config.getClientMaxBodySize());

		// 3. Add the received data chunk to our persistent request object
		_reqs[fd].addData(std::string(buff, bytes));

		// 4. Check if the request is finished OR if a size limit error occurred
		if (_reqs[fd].isComplete() || _reqs[fd].getState() == Request::ERROR)
		{
			// Case A: The request exceeded the client_max_body_size
			if (_reqs[fd].getState() == Request::ERROR)
			{
				Response	res;
				res.defaultErrorPage(413); // 413 Payload Too Large

				std::string	res_str = res.build();
				send(fd, res_str.c_str(), res_str.size(), 0);

				std::cout << "DEBUG: Request too large, sent 413" << std::endl;
			}
			// Case B: The request is valid and fully received
			else
			{
				_executeRequest(fd, _reqs[fd]);
			}
			// 5. IMPORTANT: Remove the request from the map after sending a response
			// This clears the "closet" for this client's next request
			_reqs.erase(fd);
		}
	}
	else
	{
		// Handle client disconnection (bytes == 0) or read errors (bytes < 0)
		_handleDisconnection(idx);
	}
}

void
Server::_executeRequest(int fd, Request &req)
{
	Response	res;
	std::string	path = req.getPath();

	// 1. Handle the default home page if the path is "/"
	if (path == "/")
		path = _config.getHomePage(); // Default file

	// 2. Build the full system path using the root directory from config
	std::string	fullPath = _config.getFolderRoot() + "/"
								+ (path[0] == '/' ? path.substr(1) : path);

	// GET: Used to retrieve files
	if (req.getMethod() == "GET")
	{
		std::string	content = _readFile(fullPath);
		if (!content.empty())
		{
			res.setStatus(200); // OK
			res.setBody(content);
			// It finds the right label for the box
			res.setHeader("Content-Type", Utils::getMimeType(path));

			std::cout << "DEBUG: Response sent [200 OK]" << std::endl;
		}
		else
		{
			res.defaultErrorPage(404);

			std::cout << "DEBUG: Response sent [404 Not Found]" << std::endl;
		}
	}
	// POST: Used to send data to the server
	else if (req.getMethod() == "POST")
	{
		// Open a file in append mode to save the request body
		std::ofstream	outfile("www/uploads/data.txt", std::ios::app);
		if (outfile.is_open())
		{
			outfile << req.getBody() << std::endl;
			outfile.close();

			res.setStatus(201);
			res.setBody("<html><body><h1>Post Successful!"
					"Data saved.</h1></body></html>");
		}
		else
			// Internal Server Error if file cannot be opened
			res.defaultErrorPage(500);
	}
	// DELETE: Used to remove a resource from the server
	else if (req.getMethod() == "DELETE")
	{
		// std::remove to delete a file from the disk
		if (std::remove(fullPath.c_str()) == 0)
			res.setStatus(204); // 204 No Content (Success with no body)
		else
			res.defaultErrorPage(404); // Not Found if the file doesn't exist
	}

	// 3. Build the final HTTP string and send it back to the client
	std::string	res_str = res.build();
	send(fd, res_str.c_str(), res_str.size(), 0);
}

void
Server::_handleDisconnection(int idx)
{
	int	fd = _fds[idx].fd;
	_reqs.erase(fd); // Always clean the map

	if (fd > 0)
		std::cout << "Log: Client on fd " << fd << " disconnected." << std::endl;

	_removeClient(idx);
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
	_addToPoll(_serv_fd);

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
				{
					_acceptNewConnection();  // New guest arrived
				}
				else
				{
					size_t	before = _fds.size();
					_handleClientRequest(i); // Existing guest sent data
					if (_fds.size() < before)
						i--;
				}
			}
		}
	}
}

// int	setsockopt(int sockfd, int level, int optname,
// 					const void *optval, socklen_t optlen);
// int	accept(int, sockaddr *, socklen_t *);