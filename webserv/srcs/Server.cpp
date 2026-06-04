/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/04 17:41:54 by erazumov         ###   ########.fr       */
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
	// Close main listening socket if active
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

	// 2. Set listening socket to non-blocking mode
	if (fcntl(_serv_fd, F_SETFL, O_NONBLOCK) < 0)
		perror("Fcntl non-block setup failed");

	// 3. Allow immediate local port reuse
	//    to avoid "Address already in use" errors
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

Server::ReadStatus
Server::handleRead(int client_fd)
{
	char	buff[4096];

	// 1. Read raw bytes from the client socket without blocking
	int		bytes_read = recv(client_fd, buff, sizeof(buff) - 1, 0);
	if (bytes_read <= 0)
	{
		_clearClientState(client_fd);
		return Server::READ_ERROR;
	}
	buff[bytes_read] = '\0';

	// 2. Push network data chunk into the client's dedicated Request state machine
	Request	&curr = _reqs[client_fd];

	curr.setLimit(_config.getClientMaxBodySize());
	curr.addData(std::string(buff, bytes_read));

	// Handle immediate request header or payload body limit errors
	if (curr.getState() == Request::ERROR)
	{
		std::cerr << "[Server] Request parsing error detected on fd ["
				  << client_fd << "] code: " << curr.getErrCode() << std::endl;

		Response	res;
		res.defaultErrorPage(curr.getErrCode());
		_resps[client_fd] = res;
		return Server::STATIC_READY;
	}

	// 3. Monitor if the HTTP parsing framework reached completion
	if (curr.isComplete())
	{
		std::string	path = curr.getPath();
		std::string	method = curr.getMethod();
		Response	response;

		std::cout << "[Server] Processing completed request on fd [" << client_fd
				  << "] -> " << method << " " << path << std::endl;

		// IM_A_TEAPOT 🫖
		if (path == "/coffee")
		{
			std::string	teapotHtml = "<html><head><title>418 I'm a Teapot</title></head>"
				"<body style='text-align:center; font-family:sans-serif; background-color:#fafafa; padding-top:100px;'>";
			teapotHtml += "<div style='font-size: 120px; margin-bottom:10px;'>🫖</div>"
				"<h1 style='font-size: 60px; color: #e67e22; margin: 0 0 10px 0;'>418 I'm a Teapot</h1>"
				"<h3 style='color: #2c3e50;'>HTCPCP Error: This device is a teapot. Cannot brew coffee.</h3>"
				"<hr style='width: 40%; border: 0; border-top: 1px solid #ddd; margin: 20px auto;'>"
				"<p style='color: #7f8c8d; font-style: italic;'>\"I'm a little teapot, short and stout...\"</p>"
				"<p style='color: #bdc3c7; font-size: 12px; margin-top:30px;'>webserv/1.0 (42 Paris)</p>"
				"</body></html>";

			response.setStatus(Http::IM_A_TEAPOT);
			response.setBody(teapotHtml);
			response.setHeader("Content-Type", "text/html");

			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}

		// Dynamic Location Routing Match
		const Location	*loc = _matchLocation(path);

		// Check allowed HTTP methods
		if (loc && !loc->getMethods().empty())
		{
			const std::vector<std::string>	&allowed = loc->getMethods();
			bool							methodSupported = false;

			for (size_t i = 0; i < allowed.size(); ++i)
			{
				if (allowed[i] == method)
				{
					methodSupported = true;
					break;
				}
			}
			if (!methodSupported)
			{
				response.defaultErrorPage(Http::METHOD_NOT_ALLOWED);
				_resps[client_fd] = response;
				return Server::STATIC_READY;
			}
		}

		// Check HTTP Redirection (301)
		if (loc && !loc->getRedirect().empty())
		{
			response.setStatus(Http::MOVED_PERMANENTLY);
			response.setHeader("Location", loc->getRedirect());
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}

		// --- ROBUST PATH RESOLUTION START ---
		// 1. Get the base root and default index for this location
		std::string	activeRoot = (loc && !loc->getRoot().empty()) ? loc->getRoot() : _config.getFolderRoot();
		std::string	currentIndex = (loc && !loc->getIndex().empty()) ? loc->getIndex() : _config.getHomePage();

		// 2. Resolve the relative path by removing the location prefix (essential for the tester's /directory/ route)
		std::string	relPath = path;
		if (loc)
		{
			std::string	locPath = loc->getPath();
			if (relPath.find(locPath) == 0)
				relPath = relPath.substr(locPath.length());
		}

		// 3. If the request targets a directory layout, append the default index file safely
		if (relPath.empty() || relPath[relPath.size() - 1] == '/')
		{
			if (!currentIndex.empty() && currentIndex[0] == '/')
				relPath += currentIndex.substr(1);
			else
				relPath += currentIndex;
		}

		// 4. Robust Path Joining: strip any trailing slashes from the root string
		while (!activeRoot.empty() && activeRoot[activeRoot.size() - 1] == '/')
			activeRoot.erase(activeRoot.size() - 1);

		// 5. Ensure the relative path always starts with exactly one leading slash
		if (relPath.empty() || relPath[0] != '/')
			relPath = "/" + relPath;

		// 6. Combine them into a flawless absolute path
		std::string	fullPath = activeRoot + relPath;
		// --- ROBUST PATH RESOLUTION END ---

		// CASE A: CGI Processing
		bool	isCgi = false;

		if (loc && !loc->getCgiPath().empty())
			isCgi = true;
		else if (fullPath.size() >= 3 && fullPath.substr(fullPath.size() - 3) == ".py")
			isCgi = true;
		else if (fullPath.size() >= 4 && fullPath.substr(fullPath.size() - 4) == ".php")
			isCgi = true;

		if (isCgi)
		{
			std::cout << "[Server] Executing CGI python gateway script for fd ["
					  << client_fd << "]" << std::endl;
			_cgis[client_fd] = new CGI();

			int	cgi_status = _cgis[client_fd]->execute(curr, fullPath);

			if (cgi_status == Http::INTERNAL_SERVER_ERROR)
			{
				delete _cgis[client_fd];
				_cgis.erase(client_fd);
				response.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
				_resps[client_fd] = response;
				return Server::STATIC_READY;
			}
			return Server::CGI_READY;
		}
		// CASE B: Static Resources & Location-specific Autoindex
		else
		{
			// Handle dynamic directory checks
			if (!path.empty() && path[path.size() - 1] == '/')
			{
				std::ifstream	indexCheck(fullPath.c_str());

				// If index.html doesn't exist, execute Autoindex
				if (!indexCheck.good())
				{
					indexCheck.close();
					bool		autoindexSwitch = loc ? loc->getAutoindex() : false;

					if (autoindexSwitch)
					{
						std::string	autoindexHtml = Utils::generateAutoindex(activeRoot + path, path);
						if (!autoindexHtml.empty())
						{
							response.setStatus(Http::OK);
							response.setBody(autoindexHtml);
							response.setHeader("Content-Type", "text/html");
							_resps[client_fd] = response;
							return Server::STATIC_READY;
						}
					}
					response.defaultErrorPage(Http::FORBIDDEN);
					_resps[client_fd] = response;
					return Server::STATIC_READY;
				}
				indexCheck.close();
			}
			// --- HANDLE GET METHOD ---
			if (method == "GET")
			{
				if (access(fullPath.c_str(), R_OK) != 0)
					response.defaultErrorPage(Http::NOT_FOUND);
				else
				{
					std::string	content = _readFile(fullPath);
					response.setStatus(Http::OK);
					response.setBody(content);
					response.setHeader("Content-Type", Utils::getMimeType(fullPath));
				}
			}
			// --- HANDLE POST METHOD (File Upload) ---
			else if (method == "POST")
			{
				std::string		targetUploadPath = fullPath;

				if (loc && !loc->getUploadStore().empty())
				{
					size_t		lastSlash = path.find_last_of('/');
					std::string	fileName = (lastSlash != std::string::npos)
											? path.substr(lastSlash + 1) : "uploaded_file";
					targetUploadPath = loc->getUploadStore() + "/" + fileName;
				}

				std::ofstream	outFile(targetUploadPath.c_str(), std::ios::binary);
				if (!outFile.is_open())
					response.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
				else
				{
					std::string	body = curr.getBody();
					outFile.write(body.c_str(), body.size());
					outFile.close();

					response.setStatus(Http::CREATED);
					response.setBody("<html><body><h1>201 Created</h1><p>File written successfully.</p></body></html>");
					response.setHeader("Content-Type", "text/html");
				}
			}
			// --- HANDLE DELETE METHOD (File Removal) ---
			else if (method == "DELETE")
			{
				std::ifstream	fileCheck(fullPath.c_str());
				if (!fileCheck.good())
					response.defaultErrorPage(Http::NOT_FOUND);
				else
				{
					fileCheck.close();

					if (unlink(fullPath.c_str()) == -1)
						response.defaultErrorPage(Http::FORBIDDEN);
					else
					{
						response.setStatus(Http::OK);
						response.setBody("<html><body><h1>200 OK</h1><p>File deleted successfully.</p></body></html>");
						response.setHeader("Content-Type", "text/html");
					}
				}
			}
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
	}
	return Server::READ_INCOMPLETE;
}

Server::WriteStatus
Server::handleWrite(int client_fd)
{
	if (_writeBuffs.count(client_fd) == 0)
		_writeBuffs[client_fd] = _resps[client_fd].build();

	const std::string	&res_str = _writeBuffs[client_fd];

	// Transmit data chunk through the client socket without blocking
	int					bytes_sent = send(client_fd, res_str.c_str(), res_str.size(), 0);

	// Error handling: connection dropped or network failure
	if (bytes_sent <= 0)
	{
		_clearClientState(client_fd);
		return WRITE_ERROR;
	}

	// Full response transmission success
	if (static_cast<size_t>(bytes_sent) >= res_str.size())
	{
		std::cout << "[Server] Response successfully transmitted to client fd ["
				  << client_fd << "]" << std::endl;
		_clearClientState(client_fd);
		return WRITE_COMPLETE;
	}

	// Partial write tracking
	_writeBuffs[client_fd] = res_str.substr(bytes_sent);

	return WRITE_INCOMPLETE;
}

void
Server::clearClientState(int client_fd)
{
	_reqs.erase(client_fd);
	_resps.erase(client_fd);
	_writeBuffs.erase(client_fd);

	std::map<int, CGI*>::iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		delete it->second;
		_cgis.erase(it);
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Server::_clearClientState(int client_fd)
{
	// Erase transactional data structures mapped to this client to prevent state leaks
	_reqs.erase(client_fd);
	_resps.erase(client_fd);
	_writeBuffs.erase(client_fd);

	// Safely trigger CGI destructor to release system pipes if an instance exists
	std::map<int, CGI*>::iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		delete it->second;
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

const Location
*Server::_matchLocation(const std::string &path) const
{
	const std::vector<Location>	&locs = _config.getLocations();
	const Location				*bestMatch = NULL;
	size_t						longestMatchLen = 0;

	for (size_t i = 0; i < locs.size(); ++i)
	{
		const std::string	&locPath = locs[i].getPath();
		if (locPath[0] == '.' && path.size() >= locPath.size())
		{
			if (path.substr(path.size() - locPath.size()) == locPath)
				return &locs[i];
		}

		// Check if the request URI path matches the location prefix rule
		for (size_t i = 0; i < locs.size(); ++i)
	{
		const std::string	&locPath = locs[i].getPath();
		if (locPath[0] != '.' && path.find(locPath) == 0)
		{
			if (locPath.size() > longestMatchLen)
			{
				longestMatchLen = locPath.size();
				bestMatch = &locs[i];
			}
		}
	}
	}
	return bestMatch;
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

std::string
Server::getRequestBody(int client_fd)
{
	return _reqs[client_fd].getBody();
}

void
Server::setCgiResponse(int client_fd, const Response &res)
{
	_resps[client_fd] = res;
}
