/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:20:40 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/15 19:37:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

static std::map<int, size_t>	g_bytesSent;

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
		clearClientState(client_fd);
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
	char	buff[4096];
	int		bytes_read = recv(client_fd, buff, sizeof(buff) - 1, 0);

	if (bytes_read == 0)
	{
		clearClientState(client_fd);
		return Server::READ_ERROR;
	}
	if (bytes_read < 0)
	{
		return Server::READ_INCOMPLETE;
	}

	buff[bytes_read] = '\0';
	Request	&curr = _reqs[client_fd];

	size_t	prev_size = curr.getRawSize();

	curr.setLimit(_config.getClientMaxBodySize());
	curr.addData(std::string(buff, bytes_read));

	if (curr.getState() == Request::ERROR)
	{
		Response	res;
		res.defaultErrorPage(curr.getErrCode());
		_resps[client_fd] = res;
		return Server::STATIC_READY;
	}
	if (!curr.isComplete())
	{
		size_t	curr_size = curr.getRawSize();
		size_t	milestone = 512 * 1024;

		if (curr_size > 512 * 1024 &&
		   (curr_size / milestone > prev_size / milestone))
		{
			Utils::logProgress(client_fd, curr_size);
		}
		return Server::READ_INCOMPLETE;
	}

	if (curr.getRawSize() > 512 * 1024)
	{
		Utils::clearProgress();
	}

	return _execCompetedOrder(client_fd, curr);
}

Server::WriteStatus
Server::handleWrite(int client_fd)
{
	if (_writeBuffs.count(client_fd) == 0)
	{
		// RFC Compliance: Force empty payload body for HEAD responses before serialisation
		if (_reqs.count(client_fd) && _reqs[client_fd].getMethod() == "HEAD")
		{
			_resps[client_fd].clearBodyForHead();
		}
		_writeBuffs[client_fd] = _resps[client_fd].build();
		g_bytesSent[client_fd] = 0;
	}

	const std::string	&res_str = _writeBuffs[client_fd];

	size_t	already_sent = g_bytesSent[client_fd];
	size_t	remaining = res_str.size() - already_sent;
	size_t	chunk_size = remaining > 65536 ? 65536 : remaining;

	int	bytes_sent = send(client_fd, res_str.c_str() + already_sent, chunk_size, 0);

	if (bytes_sent == 0)
	{
		g_bytesSent.erase(client_fd);
		clearClientState(client_fd);
		return WRITE_ERROR;
	}
	if (bytes_sent < 0)
	{
		return Server::WRITE_INCOMPLETE;
	}

	g_bytesSent[client_fd] += bytes_sent;

	if (g_bytesSent[client_fd] >= res_str.size())
	{
		g_bytesSent.erase(client_fd);
		_writeBuffs.erase(client_fd);
		_resps.erase(client_fd);
		return WRITE_COMPLETE;
	}
	return Server::WRITE_INCOMPLETE;
}

Server::ReadStatus
Server::clearClientState(int client_fd)
{
	_resps.erase(client_fd);
	_writeBuffs.erase(client_fd);
	g_bytesSent.erase(client_fd);

	std::map<int, CGI *>::iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		delete it->second;
		_cgis.erase(it);
	}

	// Clean up transaction context but retain leftover data inside the map
	if (_reqs.count(client_fd))
	{
		_reqs[client_fd].clearButPreserveLeftover();
	}
	return Server::READ_INCOMPLETE;
}

void
Server::cleanupCgi(int client_fd)
{
	std::map<int, CGI *>::iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
	{
		pid_t	pid = it->second->getPid();
		if (pid > 0)
		{
			kill(pid, SIGKILL);
			int	status;
			waitpid(pid, &status, 0);
		}
		delete it->second;
		_cgis.erase(it);
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

std::string
Server::_readFile(const std::string &path)
{
	std::ifstream	file(path.c_str());
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
		if (!locPath.empty() && locPath[0] != '.' && path.find(locPath) == 0)
		{
			if (locPath.size() > longestMatchLen)
			{
				longestMatchLen = locPath.size();
				bestMatch = &locs[i];
			}
		}
	}
	return bestMatch;
}

/* ------------------------------- handeRead() ------------------------------ */

int
Server::_active_cgis = 0;

Server::ReadStatus
Server::_execCompetedOrder(int client_fd, Request &req)
{
	 // ADD THIS DEBUG BLOCK:
    std::cout << "\n=== REQUEST ===" << std::endl;
    std::cout << "Method: " << req.getMethod() << std::endl;
    std::cout << "Path: " << req.getPath() << std::endl;
    std::cout << "Version: " << req.getVersion() << std::endl;
    std::cout << "State: " << req.getState() << std::endl;
    std::cout << "Has Host header: " << (req.getHeader("Host").empty() ? "NO" : "YES") << std::endl;
    if (!req.getHeader("Host").empty())
        std::cout << "Host value: '" << req.getHeader("Host") << "'" << std::endl;
    std::cout << "================" << std::endl;

	// Check if the Request parser flagged an HTTP parsing state error (e.g., malformed headers)
	// if (req.getState() == Request::ERROR)
	// {
	// 	Response	res;
	// 	res.defaultErrorPage(req.getErrCode());
	// 	_resps[client_fd] = res;
	// 	return Server::STATIC_READY;
	// }

	std::string	rawPath = req.getPath();
	std::string	method = req.getMethod();

	// 1. SECURITY FIX: Validate path sequences to block Path Traversal directory escapes ("..")
	if (rawPath.find("..") != std::string::npos)
	{
		Response	response;
		response.defaultErrorPage(Http::BAD_REQUEST);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// 2. CGI FIX: Isolate and parse the Query String parameters out of the incoming URI path
	std::string	path = rawPath;
	std::string	queryString = "";
	size_t		qPos = path.find('?');
	if (qPos != std::string::npos)
	{
		queryString = path.substr(qPos + 1);
		path = path.substr(0, qPos);
	}

	// Clear outstanding I/O feedback stream indicators and output standardized access metrics
	Utils::logRequest(method, path);
	Response	response;

	// A. RFC Exception: Evaluate special teapot benchmark context ("/coffee")
	if (path == "/coffee")
	{
		std::string	teapotHtml = _readFile("./www/418.html");
		if (teapotHtml.empty())
		{
			teapotHtml = "<html><head><title>418 I'm a Teapot</title></head><body><h1>418 I'm a Teapot</h1></body></html>";
		}
		response.setStatus(Http::IM_A_TEAPOT);
		response.setBody(teapotHtml);
		response.setHeader("Content-Type", "text/html");
		response.setHeader("Content-Length", Utils::toStr(teapotHtml.size()));
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// Match the sanitized URI path against configured route scopes (locations)
	const Location	*loc = _matchLocation(path);

	// B. Request Body Limit Check: Enforce location-specific constraints, falling back to global max
	size_t	max_body = (loc && loc->getClientMaxBodySize() > 0)
					   ? loc->getClientMaxBodySize()
					   : _config.getClientMaxBodySize();
	if (req.getBody().size() > max_body)
	{
		response.defaultErrorPage(Http::PAYLOAD_TOO_LARGE);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// C. HTTP Method Validation: Verify if the requested method token is authorized for this route
	if (!_checkIncMethod(loc, method))
	{
		response.defaultErrorPage(Http::METHOD_NOT_ALLOWED);
		if (method == "HEAD")
			response.setBody("");
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// D. HTTP Redirection: Evaluate route redirection context rules (301 Moved Permanently)
	if (loc && !loc->getRedirect().empty())
	{
		std::string			redir = loc->getRedirect();
		int					status = Http::MOVED_PERMANENTLY; // Fallback to 301
		std::string			url = redir;
		std::stringstream	r_ss(redir);
		int					custom_status;

		// FIX: Dynamically parse explicit status codes (301/302) from configuration token paths
		if (r_ss >> custom_status)
		{
			if (custom_status >= 300 && custom_status < 400)
			{
				status = custom_status;
				r_ss >> url;
				if (url.empty())
					url = redir.substr(redir.find_first_of(" \t") + 1);
				url = Utils::trim(url);
			}
		}
		response.setStatus(status);
		response.setHeader("Location", url);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// E. Resolve Document Root System Paths
	std::string	activeRoot = loc && !loc->getRoot().empty()
							? loc->getRoot() : _config.getFolderRoot();
	std::string	relPath = path;

	// Strip matched location prefix paths for cleaner disk workspace alignments
	if (loc && relPath.find(loc->getPath()) == 0)
	{
		relPath = relPath.substr(loc->getPath().length());
		if (!relPath.empty() && relPath[0] != '/')
			relPath = "/" + relPath;
	}

	// Sanitize paths by stripping trailing delimiters out of activeRoot
	while (!activeRoot.empty() && activeRoot[activeRoot.size() - 1] == '/')
		activeRoot.erase(activeRoot.size() - 1);

	// Construct absolute server system workplace resource string
	std::string	fullPath = activeRoot + (relPath.empty() || relPath[0] != '/'
							? "/" + relPath : relPath);

	// Evaluate index route constraints if resource points to a directory
	if (!path.empty() && path[path.size() - 1] == '/')
	{
		std::string	indexFile = (loc && !loc->getIndex().empty())
								? loc->getIndex() : _config.getHomePage();
		if (indexFile.empty())
			indexFile = "index.html";
		fullPath = fullPath + (fullPath[fullPath.size() - 1] == '/'
							   ? "" : "/") + indexFile;
	}

	// F. CGI Configuration Match Matrix: Map targeted extensions to available interpreter layouts
	std::string	cgiBin = "";
	const std::vector<Location>	&allLocs = _config.getLocations();
	for (size_t i = 0; i < allLocs.size(); ++i)
	{
		const std::string	&ext = allLocs[i].getPath();
		if (!ext.empty() && ext[0] == '.' && path.size() >= ext.size())
		{
			if (path.substr(path.size() - ext.size()) == ext)
			{
				cgiBin = allLocs[i].getCgiPath();
				break;
			}
		}
	}

	// G. CGI Execution Control Context
	if (!cgiBin.empty())
	{
		struct stat	cgi_s;
		// Reject targeted CGI executions if resource does not point to a valid file layout on disk
		if (stat(fullPath.c_str(), &cgi_s) != 0 || S_ISDIR(cgi_s.st_mode))
		{
			response.defaultErrorPage(Http::NOT_FOUND);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}

		_active_cgis++;
		_cgis[client_fd] = new CGI();

		// Spawn independent non-blocking executor layout
		int	cgi_status = _cgis[client_fd]->execute(req, fullPath, cgiBin, Utils::toStr(_port));
		if (cgi_status == Http::INTERNAL_SERVER_ERROR)
		{
			_active_cgis--;
			delete _cgis[client_fd];
			_cgis.erase(client_fd);
			response.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
			_resps[client_fd] = response;
			return Server::STATIC_READY;
		}
		return Server::CGI_READY; // Successfully bound asynchronously into the main multiplexer map
	}

	// H. File System Verification & Autoindex Evaluation
	struct stat	path_stat;
	if (stat(fullPath.c_str(), &path_stat) != 0)
	{
		response.defaultErrorPage(Http::NOT_FOUND);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// If targeted resource path resolves directly to a directory configuration context
	if (S_ISDIR(path_stat.st_mode))
	{
		if (loc && loc->getAutoindex())
		{
			std::string	autoindexHtml = Utils::generateAutoindex(fullPath, path);
			if (!autoindexHtml.empty())
			{
				Response	autoResponse;
				autoResponse.setStatus(Http::OK);
				autoResponse.setBody(autoindexHtml);
				autoResponse.setHeader("Content-Type", "text/html");
				_resps[client_fd] = autoResponse;
				return Server::STATIC_READY;
			}
		}
		response.defaultErrorPage(Http::FORBIDDEN);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	// G. Default Index Resolution: Backup structural path checks
	std::string	finalRelPath = relPath;
	if (finalRelPath.empty() || finalRelPath[finalRelPath.size() - 1] == '/')
	{
		std::string	currIndex = (loc && !loc->getIndex().empty())
								? loc->getIndex() : _config.getHomePage();
		if (!currIndex.empty())
		{
			if (currIndex[0] == '/')
				finalRelPath += currIndex.substr(1);
			else
				finalRelPath += currIndex;
			fullPath = activeRoot + finalRelPath;
		}
	}

	// J. Route to Isolated Method Handlers
	if (method == "GET")
		return _runStaticGet(client_fd, fullPath);
	if (method == "POST")
		return _runStaticPostUpload(client_fd, fullPath);
	if (method == "DELETE")
		return _runStaticDeleteFile(client_fd, fullPath);

	// Fallback: If method is not supported or matched, return 405 Method Not Allowed
	Response	finalResponse;
	finalResponse.defaultErrorPage(Http::METHOD_NOT_ALLOWED);
	if (method == "HEAD")
		finalResponse.setBody("");
	_resps[client_fd] = finalResponse;
	return Server::STATIC_READY;
}

bool
Server::_checkIncMethod(const Location *loc, const std::string &method) const
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

bool
Server::_isCgiResource(const Location *loc, const std::string &,
											const std::string &) const
{
	if (loc && !loc->getCgiPath().empty())
		return true;
	return false;
}

Server::ReadStatus
Server::_runStaticGet(int client_fd, std::string fullPath)
{
	Response		response;
	struct stat		s;
	if (stat(fullPath.c_str(), &s) != 0 || S_ISDIR(s.st_mode))
	{
		response.defaultErrorPage(Http::NOT_FOUND);
		_resps[client_fd] = response;
		return Server::STATIC_READY;
	}

	std::string	content = _readFile(fullPath);
	response.setStatus(Http::OK);
	response.setHeader("Content-Length", Utils::toStr(content.size()));
	response.setHeader("Content-Type", Utils::getMimeType(fullPath));
	response.setBody(content);
	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

Server::ReadStatus
Server::_runStaticHead(int client_fd, std::string fullPath)
{
	Response		response;
	Request			&req = _reqs[client_fd];
	std::string		origPath = req.getPath();
	const Location	*loc = _matchLocation(origPath);

	struct stat		path_stat;
	bool			isDir = false;

	if (::stat(fullPath.c_str(), &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		isDir = true;
	if (isDir)
	{
		if (origPath.empty() || origPath[origPath.size() - 1] != '/')
			fullPath += '/';

		std::string	indexFile = loc ? loc->getIndex() : _config.getHomePage();
		if (indexFile.empty())
			indexFile = "index.html";

		std::string	indexPath = fullPath;
		if (!indexPath.empty() && indexPath[indexPath.size() - 1] != '/')
			indexPath += "/";
		indexPath += indexFile;

		bool	hasIndex = (access(indexPath.c_str(), R_OK) == 0);
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
		std::string	content = _readFile(fullPath);
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
	Response		response;
	Request			&req = _reqs[client_fd];
	const Location	*loc = _matchLocation(req.getPath());
	std::string		targetPath = fullPath;

	if (loc && !loc->getUploadStore().empty())
	{
		std::string	store = loc->getUploadStore();
		size_t		lastSlash = req.getPath().find_last_of('/');
		std::string	fileName = (lastSlash != std::string::npos)
								? req.getPath().substr(lastSlash + 1) : "file.bin";
		if (fileName.empty()) fileName = "file.bin";
		targetPath = store + (store[store.size() - 1] == '/' ? "" : "/") + fileName;
	}

	std::ofstream	outFile(targetPath.c_str(), std::ios::binary);
	if (!outFile.is_open())
	{
		response.defaultErrorPage(Http::INTERNAL_SERVER_ERROR);
	}
	else
	{
		outFile.write(req.getBody().c_str(), req.getBody().size());
		outFile.close();
		response.setStatus(Http::CREATED);
		response.setBody("<html><body><h1>201 Created</h1></body></html>");
		response.setHeader("Content-Type", "text/html");
	}
	_resps[client_fd] = response;
	return Server::STATIC_READY;
}

Server::ReadStatus
Server::_runStaticDeleteFile(int client_fd, std::string fullPath)
{
	Response		response;
	std::ifstream	fileCheck(fullPath.c_str());

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

Server::ReadStatus
Server::_runDirRedirect(int client_fd, const std::string &reqPath)
{
	Response	response;
	std::string	loc = reqPath;

	if (loc.empty() || loc[loc.size() - 1] != '/')
		loc += "/";

	std::string	host = _reqs[client_fd].getHeader("Host");
	if (!host.empty())
		response.setHeader("Location", "http://" + host + loc);
	else
		response.setHeader("Location", loc);

	response.setStatus(Http::MOVED_PERMANENTLY);
	response.setHeader("Location", loc);
	response.setHeader("Content-Type", "text/html");
	response.setHeader("Content-Length", "0");
	response.setHeader("Connection", "close");

	Utils::logResponse(Http::MOVED_PERMANENTLY, reqPath);

	_resps[client_fd] = response;
	return Server::STATIC_READY;
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

const std::string
&Server::getRequestBody(int client_fd)
{
	return _reqs[client_fd].getBody();
}

void
Server::setCgiResponse(int client_fd, const Response &res)
{
	_resps[client_fd] = res;
}

int
Server::getActiveCgis()
{
	return _active_cgis;
}

void
Server::setActiveCgis(int count)
{
	_active_cgis = count;
}

pid_t
Server::getCgiPid(int client_fd) const
{
	std::map<int, CGI *>::const_iterator	it = _cgis.find(client_fd);
	if (it != _cgis.end())
		return it->second->getPid();
	return -1;
}
