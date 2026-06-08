/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 00:35:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Server::Server(const Config &config) : _serv_fd(-1),
									   _port(config.getPort()),
									   _config(config)
{
	memset(&_addr, 0, sizeof(_addr));
}

Server::Server(const Server &copy) : _serv_fd(-1),
									 _port(copy._port),
									 _config(copy._config)
{
	memset(&_addr, 0, sizeof(_addr));
}

// Private
Server &Server::operator=(const Server &other)
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
	std::map<int, Request>::iterator it = _reqs.begin();
	while (it != _reqs.end())
	{
		int client_fd = it->first;

		it++;

		close(client_fd);
		clearClientState(client_fd);
	}
}

/* ------------------------------ CORE METHODS ------------------------------ */

void Server::setup()
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
	int opt = 1;
	if (setsockopt(_serv_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		perror("Setsockopt REUSEADDR failed");

	// 4. Configure Socket Address Structure
	_addr.sin_family = AF_INET;			// IPv4 addresses
	_addr.sin_addr.s_addr = INADDR_ANY; // Listen on all network interfaces
	_addr.sin_port = htons(_port);		// Convert port to Network Byte Order

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
	char buff[4096];

	// 1. Read raw bytes from the client socket without blocking
	int bytes_read = recv(client_fd, buff, sizeof(buff) - 1, 0);
	if (bytes_read <= 0)
	{
		clearClientState(client_fd);
		return Server::READ_ERROR;
	}
	buff[bytes_read] = '\0';

	// 2. Push network data chunk into the client's dedicated Request state machine
	Request &curr = _reqs[client_fd];
	curr.setLimit(_config.getClientMaxBodySize());
	curr.addData(std::string(buff, bytes_read));

	// 3. Handle immediate request header or payload body limit errors
	if (curr.getState() == Request::ERROR)
	{
		Response res;
		res.defaultErrorPage(curr.getErrCode());
		_resps[client_fd] = res;
		return Server::STATIC_READY;
	}

	// 4. Monitor if the HTTP parsing framework reached completion
	if (!curr.isComplete())
		return Server::READ_INCOMPLETE;

	// 5. Request is fully ready, forward it to the flat dispatcher
	return _execCompetedOrder(client_fd, curr);
}

Server::WriteStatus
Server::handleWrite(int client_fd)
{
	if (_writeBuffs.count(client_fd) == 0)
	{
		// FOR HEAD REQUESTS: Force empty body BEFORE building the response
		if (_reqs.count(client_fd) && _reqs[client_fd].getMethod() == "HEAD")
		{
			_resps[client_fd].clearBodyForHead(); // Make sure this method exists
												  // OR directly: _resps[client_fd].setBody("");
		}
		_writeBuffs[client_fd] = _resps[client_fd].build();
	}

	const std::string &res_str = _writeBuffs[client_fd];
	int bytes_sent = send(client_fd, res_str.c_str(), res_str.size(), 0);

	if (bytes_sent <= 0)
	{
		clearClientState(client_fd);
		return WRITE_ERROR;
	}
	if (static_cast<size_t>(bytes_sent) >= res_str.size())
	{
		std::cout << "[Server] Response successfully transmitted to client fd ["
				  << client_fd << "]" << std::endl;
		return WRITE_COMPLETE;
	}
	_writeBuffs[client_fd] = res_str.substr(bytes_sent);
	return Server::WRITE_INCOMPLETE;
}

Server::ReadStatus
Server::clearClientState(int client_fd)
{
	_resps.erase(client_fd);
	_writeBuffs.erase(client_fd);

	std::map<int, CGI *>::iterator it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		delete it->second;
		_cgis.erase(it);
	}

	// Clean up transaction context but retain leftover data inside the map
	if (_reqs.count(client_fd))
	{
		_reqs[client_fd].clearButPreserveLeftover();
		if (_reqs[client_fd].isComplete())
		{
			return _execCompetedOrder(client_fd, _reqs[client_fd]);
		}
	}
	return Server::READ_INCOMPLETE;
}

void Server::cleanupCgi(int client_fd)
{
	std::map<int, CGI *>::iterator it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		pid_t pid = it->second->getPid();
		if (pid > 0)
		{
			int status;
			waitpid(pid, &status, WNOHANG);
			std::cout << "[Server] Cleaned up CGI process " << pid << std::endl;
		}
		delete it->second;
		_cgis.erase(it);
	}
}
/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

std::string
Server::_readFile(const std::string &path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		return "";

	std::stringstream buff;
	buff << file.rdbuf();
	return buff.str();
}

const Location *Server::_matchLocation(const std::string &path) const
{
	const std::vector<Location> &locs = _config.getLocations();
	const Location *bestMatch = NULL;
	size_t longestMatchLen = 0;

	for (size_t i = 0; i < locs.size(); ++i)
	{
		const std::string &locPath = locs[i].getPath();

		if (!locPath.empty() && locPath[0] != '.' && path.find(locPath) == 0)
		{
			if (locPath.size() > longestMatchLen)
			{
				longestMatchLen = locPath.size();
				bestMatch = &locs[i];
			}
		}
	}
	if (bestMatch != NULL)
		return bestMatch;

	for (size_t i = 0; i < locs.size(); ++i)
	{
		const std::string &locPath = locs[i].getPath();

		if (!locPath.empty() && locPath[0] == '.' && path.size() >= locPath.size())
		{
			if (path.substr(path.size() - locPath.size()) == locPath)
				return &locs[i];
		}
	}
	return NULL;
}

/* ------------------------------- handeRead() ------------------------------ */

Server::ReadStatus
Server::_execCompetedOrder(int client_fd, Request &req)
{
	Utils::logRequest(req.getMethod(), req.getPath());

	std::string	path = req.getPath();
	std::string	method = req.getMethod();
	Response	response;

	// A. Teapot Verification 🫖
	if (path == "/coffee")
	{
		std::string teapotHtml = "<html><head><title>418 I'm a Teapot</title></head>"
								 "<body><h1>418 I'm a Teapot</h1></body></html>";
		response.setStatus(Http::IM_A_TEAPOT);
		response.setBody(teapotHtml);
		response.setHeader("Content-Type", "text/html");
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	const Location	*loc = _matchLocation(path);

	// B. Request Body Limit Check
	if (loc && loc->getClientMaxBodySize() > 0 &&
		req.getBody().size() > loc->getClientMaxBodySize())
	{
		response.defaultErrorPage(Http::PAYLOAD_TOO_LARGE);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// C. HTTP Method Validation
	if (!_checkIncMethod(loc, method))
	{
		response.defaultErrorPage(Http::METHOD_NOT_ALLOWED);
		if (method == "HEAD")
			response.setBody(""); // response.setSendBody(flase);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// D. HTTP Redirection (301)
	if (loc && !loc->getRedirect().empty())
	{
		response.setStatus(Http::MOVED_PERMANENTLY);
		response.setHeader("Location", loc->getRedirect());
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// E. Resolve Base Paths
	std::string	activeRoot = (loc && !loc->getRoot().empty())
								 ? loc->getRoot()
								 : _config.getFolderRoot();
	std::string	relPath = path;
	if (loc && relPath.find(loc->getPath()) == 0)
		relPath = relPath.substr(loc->getPath().length());

	while (!activeRoot.empty() && activeRoot[activeRoot.size() - 1] == '/')
		activeRoot.erase(activeRoot.size() - 1);

	std::string	normalRelPath = relPath;
	if (normalRelPath.empty() || normalRelPath[0] != '/')
		normalRelPath = "/" + normalRelPath;

	// F. CGI Gateway Check
	if (_isCgiResource(loc, method, normalRelPath))
	{
		std::string	cgiPath = activeRoot + normalRelPath;
		_cgis[client_fd] = new CGI();
		int cgi_status = _cgis[client_fd]->execute(req, cgiPath);
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

	// G. Default Index Resolution
	std::string	finalRelPath = normalRelPath;
	if (finalRelPath.empty() || finalRelPath[finalRelPath.size() - 1] == '/')
	{
		std::string	currIndex = (loc && !loc->getIndex().empty())
									? loc->getIndex()
									: _config.getHomePage();
		if (!currIndex.empty())
		{
			if (currIndex[0] == '/')
				finalRelPath += currIndex.substr(1);
			else
				finalRelPath += currIndex;
		}
	}
	std::string	fullPath = activeRoot + finalRelPath;

	// H. Autoindex Management
	if (!path.empty() && path[path.size() - 1] == '/')
	{
		std::ifstream	indexCheck(fullPath.c_str());
		if (!indexCheck.good())
		{
			indexCheck.close();
			if (loc && loc->getAutoindex())
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

	// I. Route to Isolated Method Handlers
	if (method == "GET")
		return _runStaticGet(client_fd, fullPath);
	if (method == "HEAD")
		return _runStaticHead(client_fd, fullPath);
	if (method == "POST")
		return _runStaticPostUpload(client_fd, fullPath);
	if (method == "DELETE")
		return _runStaticDeleteFile(client_fd, fullPath);

	response.defaultErrorPage(Http::BAD_REQUEST);
	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

bool Server::_checkIncMethod(const Location *loc, const std::string &method) const
{
	if (!loc)
		return true;

	const std::vector<std::string>	&allowed = loc->getMethods();
	if (allowed.empty())
	{
		if (loc->getPath() == "/" && method != "GET" && method != "HEAD")
			return false;
		return true;
	}
	for (size_t i = 0; i < allowed.size(); ++i)
	{
		if (allowed[i] == method)
			return true;
	}
	return false;
}

bool Server::_isCgiResource(const Location *loc, const std::string &method, const std::string &path) const
{
	if (loc && !loc->getCgiPath().empty())
		return true;
	if (method == "POST" && path.size() >= 4 && path.substr(path.size() - 4) == ".bla")
		return true;
	if (path.size() >= 3 && path.substr(path.size() - 3) == ".py")
		return true;
	if (path.size() >= 4 && path.substr(path.size() - 4) == ".php")
		return true;

	return false;
}

Server::ReadStatus
Server::_runStaticGet(int client_fd, std::string fullPath)
{
	Response response;
	Request &req = _reqs[client_fd];
	std::string origPath = req.getPath();
	const Location *loc = _matchLocation(origPath);

	struct stat path_stat;
	bool isDir = false;

	if (::stat(fullPath.c_str(), &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		isDir = true;

	if (isDir)
	{
		std::string indexFile = loc ? loc->getIndex() : _config.getHomePage();
		if (indexFile.empty())
			indexFile = "index.html";

		std::string indexPath = fullPath;
		if (!indexPath.empty() && indexPath[indexPath.size() - 1] != '/')
			indexPath += "/";
		indexPath += indexFile;

		bool hasIndex = (access(indexPath.c_str(), R_OK) == 0);

		if (origPath.empty() || origPath[origPath.size() - 1] != '/')
		{
			if (hasIndex)
			{
				response.setStatus(Http::MOVED_PERMANENTLY);
				response.setHeader("Location", origPath + "/");
				_resps[client_fd] = response;
				return Server::STATIC_READY;
			}
			response.defaultErrorPage(Http::NOT_FOUND);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
		if (!hasIndex)
		{
			response.defaultErrorPage(Http::NOT_FOUND);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
		fullPath = indexPath;
	}
	if (access(fullPath.c_str(), R_OK) != 0)
	{
		response.defaultErrorPage(Http::NOT_FOUND);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	std::ifstream file(fullPath.c_str());
	if (!file.is_open())
	{
		response.defaultErrorPage(Http::NOT_FOUND);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// For GET request: read file contents and build full response
	std::string content = _readFile(fullPath);
	response.setStatus(Http::OK);
	response.setHeader("Content-Length", Utils::toStr(content.size()));
	response.setHeader("Content-Type", Utils::getMimeType(fullPath));
	response.setBody(content);

	Utils::logResponse(response.getStatus(), _reqs[client_fd].getPath());

	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

Server::ReadStatus
Server::_runStaticHead(int client_fd, std::string fullPath)
{
	Response response;
	Request &req = _reqs[client_fd];
	std::string origPath = req.getPath();
	const Location *loc = _matchLocation(origPath);

	struct stat path_stat;
	bool isDir = false;

	if (::stat(fullPath.c_str(), &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		isDir = true;

	if (isDir)
	{
		std::string indexFile = loc ? loc->getIndex() : "index.html";
		if (indexFile.empty())
			indexFile = "youpi.bad_extension";

		std::string indexPath = fullPath;
		if (indexPath.empty() || indexPath[indexPath.size() - 1] != '/')
			indexPath += "/";
		indexPath += indexFile;

		bool hasIndex = (access(indexPath.c_str(), R_OK) == 0);

		if (origPath.empty() || origPath[origPath.size() - 1] != '/')
		{
			if (hasIndex)
			{
				response.setStatus(Http::MOVED_PERMANENTLY);
				response.setHeader("Location", origPath + "/");
				_resps[client_fd] = response;
				return Server::STATIC_READY;
			}
			response.defaultErrorPage(Http::NOT_FOUND);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
		if (!hasIndex)
		{
			response.defaultErrorPage(Http::NOT_FOUND);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
		fullPath = indexPath;
	}
	if (access(fullPath.c_str(), R_OK) != 0)
	{
		response.defaultErrorPage(Http::NOT_FOUND);
	}
	else
	{
		std::string content = _readFile(fullPath);
		response.setStatus(Http::OK);
		response.setHeader("Content-Length", Utils::toStr(content.size()));
		response.setHeader("Content-Type", Utils::getMimeType(fullPath));
	}
	Utils::logResponse(response.getStatus(), _reqs[client_fd].getPath());

	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

Server::ReadStatus
Server::_runStaticPostUpload(int client_fd, std::string fullPath)
{
	Response response;
	Request &req = _reqs[client_fd];
	const Location *loc = _matchLocation(req.getPath());
	std::string targetUploadPath = fullPath;

	if (loc && !loc->getUploadStore().empty())
	{
		size_t lastSlash = req.getPath().find_last_of('/');
		std::string fileName = (lastSlash != std::string::npos)
								   ? req.getPath().substr(lastSlash + 1)
								   : "uploaded_file";
		targetUploadPath = loc->getUploadStore() + "/" + fileName;
	}

	std::ofstream outFile(targetUploadPath.c_str(), std::ios::binary);
	if (!outFile.is_open())
	{
		response.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
	}
	else
	{
		std::string body = req.getBody();
		outFile.write(body.c_str(), body.size());
		outFile.close();

		response.setStatus(Http::CREATED);
		response.setBody("<html><body><h1>201 Created</h1></body></html>");
		response.setHeader("Content-Type", "text/html");
		response.setHeader("Connection", "close");
	}
	Utils::logResponse(response.getStatus(), _reqs[client_fd].getPath());

	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

Server::ReadStatus
Server::_runStaticDeleteFile(int client_fd, std::string fullPath)
{
	Response response;
	std::ifstream fileCheck(fullPath.c_str());

	if (!fileCheck.good())
	{
		response.defaultErrorPage(Http::NOT_FOUND);
	}
	else
	{
		fileCheck.close();
		if (unlink(fullPath.c_str()) == -1)
		{
			response.defaultErrorPage(Http::FORBIDDEN);
		}
		else
		{
			response.setStatus(Http::OK);
			response.setBody("<html><body><h1>200 OK</h1></body></html>");
			response.setHeader("Content-Type", "text/html");
			response.setHeader("Connection", "close");
		}
	}
	Utils::logResponse(response.getStatus(), _reqs[client_fd].getPath());

	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

/* -------------------------------- GETTERS --------------------------------- */

int Server::getServerFd() const
{
	return _serv_fd;
}

int Server::getReadFd(int client_fd)
{
	return _cgis[client_fd]->getReadFd();
}

int Server::getWriteFd(int client_fd)
{
	return _cgis[client_fd]->getWriteFd();
}

std::string
Server::getRequestBody(int client_fd)
{
	return _reqs[client_fd].getBody();
}

void Server::setCgiResponse(int client_fd, const Response &res)
{
	_resps[client_fd] = res;
}
