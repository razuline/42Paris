/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 20:10:43 by erazumov         ###   ########.fr       */
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
		_clearClientState(client_fd);
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

/* ------------------------------ CORE METHODS ------------------------------ */

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

	if (_reqs[client_fd].getState() == ERROR)
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
		std::string	rawPath = path;

		if (path == "/")
			path = _config.getHomePage();

		std::string	fullPath = _config.getFolderRoot() + "/" + (path[0] == '/' ? path.substr(1) : path);

		// CASE A: CGI Processing
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
		// CASE B: Static Resources & Autoindex
		else
		{
			Response	response;
			std::string	method = _reqs[client_fd].getMethod();

			// --- AUTOINDEX LOGIC FOR DIRECTORIES ---
			// Check if requested path is a directory (ends with '/' or matching logic)
			if (!rawPath.empty() && rawPath[rawPath.size() - 1] == '/')
			{
				std::string			indexFile = fullPath;
				std::ifstream		indexCheck(indexFile.c_str());

				// If index.html doesn't exist, execute Autoindex
				if (!indexCheck.good())
				{
					indexCheck.close();
					bool			isAutoindexEnabled = true;

					if (isAutoindexEnabled)
					{
						std::string	autoindexHtml =
							Utils::generateAutoindex(_config.getFolderRoot() +
								rawPath, rawPath);
						if (!autoindexHtml.empty())
						{
							response.setStatus(200);
							response.setBody(autoindexHtml);
							response.setHeader("Content-Type", "text/html");
							_resps[client_fd] = response;
							return 2;
						}
					}
					response.defaultErrorPage(403);
					_resps[client_fd] = response;
					return 2;
				}
				indexCheck.close();
			}
			// --- HANDLE GET METHOD ---
			if (method == "GET")
			{
				std::string	content = _readFile(fullPath);
				if (content.empty())
					response.defaultErrorPage(404);
				else
				{
					response.setStatus(200);
					response.setBody(content);
					// Dynamic MIME type detection using your Utils module
					response.setHeader("Content-Type", Utils::getMimeType(fullPath));
				}
			}
			// --- HANDLE POST METHOD (File Upload) ---
			else if (method == "POST")
			{
				std::ofstream	outFile(fullPath.c_str(), std::ios::binary);

				if (!outFile.is_open())
					response.defaultErrorPage(500);
				else
				{
					// Get the raw payload body received from the client
					std::string	body = _reqs[client_fd].getBody();

					// Write the exact bytes into the file
					outFile.write(body.c_str(), body.size());
					outFile.close();

					response.setStatus(201);
					response.setBody("<html><body><h1>201 Created</h1><p>File uploaded successfully.</p></body></html>");
					response.setHeader("Content-Type", "text/html");
				}
			}
			// --- HANDLE DELETE METHOD (File Removal) ---
			else if (method == "DELETE")
			{
				// 1. Check if the file actually exists before trying to delete it
				std::ifstream	fileCheck(fullPath.c_str());
				if (!fileCheck.good())
					response.defaultErrorPage(404);
				else
				{
					fileCheck.close();

					// 2. Execute the system call to erase the file from the disk
					if (unlink(fullPath.c_str()) == -1)
						response.defaultErrorPage(403);
					else
					{
						response.setStatus(200);
						response.setBody("<html><body><h1>200 OK</h1><p>File deleted successfully.</p></body></html>");
						response.setHeader("Content-Type", "text/html");
					}
				}
			}
			// --- HANDLE UNKNOWN/UNSUPPORTED METHOD ---
			else
				response.defaultErrorPage(405);

			_resps[client_fd] = response;
			return 2; // Switch client from POLLIN to POLLOUT
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
