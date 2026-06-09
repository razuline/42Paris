/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:46:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 15:19:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
#include "Utils.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Config::Config() :
	_port(8080),
	_serverName(""),
	_folderRoot(""),
	_homePage(""),
	_clientMaxBodySize(1048576),
	_locations()
{
}

Config::Config(const Config &copy) :
	_port(copy._port),
	_serverName(copy._serverName),
	_folderRoot(copy._folderRoot),
	_homePage(copy._homePage),
	_clientMaxBodySize(copy._clientMaxBodySize),
	_locations(copy._locations)
{
}

Config
&Config::operator=(const Config &other)
{
	if (this != &other)
	{
		_port = other._port;
		_serverName = other._serverName;
		_folderRoot = other._folderRoot;
		_homePage = other._homePage;
		_clientMaxBodySize = other._clientMaxBodySize;
		_locations = other._locations;
	}
	return *this;
}

Config::~Config()
{
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Config::parse(const std::string &filename)
{
	// 1. Create the file stream object
	std::ifstream	file(filename.c_str());
	std::string		line;

	// 2. Check if the STREAM is open
	if (!file.is_open())
	{
		std::cerr << "[Config] Error: Cannot open config file " << filename << std::endl;
		return;
	}

	while (std::getline(file, line))
	{
		// 1. Remove comments
		size_t	commentPos = line.find("#");
		if (commentPos != std::string::npos)
			line.erase(commentPos);

		// 2. Trim the line with only spaces and tabs
		line = Utils::trim(line);
		if (line.empty())
			continue;

		// 3. If NOT empty, look for keywords "listen"
		if (line.find("listen") == 0)
		{
			std::string			value = Utils::trim(line.substr(6));
			std::stringstream	ss(value);
			ss >> _port;
		}
		// "root"
		else if (line.find("root") == 0)
			_folderRoot = Utils::trim(line.substr(4));
		// "server_name"
		else if (line.find("server_name") == 0)
			_serverName = Utils::trim(line.substr(11));
		// "index"
		else if (line.find("index") == 0)
			_homePage = Utils::trim(line.substr(5));
		// "client_max_body_size"
		else if (line.find("client_max_body_size") == 0)
		{
			std::string			value = Utils::trim(line.substr(20));
			std::stringstream	ss(value);
			ss >> _clientMaxBodySize;
		}
		// --- LOCATION PARSING ---
		else if (line.find("location") == 0)
		{
			Location	loc;
			size_t		pathStart = 8;
			size_t		bracketPos = line.find("{");

			std::string	rawPath = line.substr(pathStart,
				(bracketPos != std::string::npos
					? bracketPos - pathStart
					: std::string::npos));
			loc.setPath(Utils::trim(rawPath));

			// Sub-loop to read the inner context of the bracket block
			while (std::getline(file, line) && Utils::trim(line) != "}")
			{
				size_t	innerComment = line.find("#");
				if (innerComment != std::string::npos)
					line.erase(innerComment);

				line = Utils::trim(line);
				if (line.empty())
					continue;

				if (line.find("root") == 0)
					loc.setRoot(Utils::trim(line.substr(4)));
				else if (line.find("index") == 0)
					loc.setIndex(Utils::trim(line.substr(5)));
				else if (line.find("return") == 0)
					loc.setRedirect(Utils::trim(line.substr(6)));
				else if (line.find("upload_store") == 0)
					loc.setUploadStore(Utils::trim(line.substr(12)));
				else if (line.find("client_max_body_size") == 0)
				{
					std::string			value = Utils::trim(line.substr(20));
					std::stringstream	ss(value);
					size_t				localSize = 0;
					ss >> localSize;
					loc.setClientMaxBodySize(localSize);
				}
				else if (line.find("autoindex") == 0)
				{
					std::string	flag = Utils::trim(line.substr(9));
					loc.setAutoindex(flag == "on");
				}
				else if (line.find("cgi_path") == 0)
				{
					loc.setCgiPath(Utils::trim(line.substr(8)));
				}
				else if (line.find("allow_methods") == 0)
				{
					std::vector<std::string>	methods;
					std::stringstream			mss(Utils::trim(line.substr(13)));
					std::string					methodToken;
					while (mss >> methodToken)
						methods.push_back(methodToken);
					loc.setMethods(methods);
				}
			}
			_locations.push_back(loc);
		}
	}
	file.close();
}

/* -------------------------------- GETTERS --------------------------------- */

int
Config::getPort() const
{
	return _port;
}

const std::string
&Config::getFolderRoot() const
{
	return _folderRoot;
}

const std::string
&Config::getServerName() const
{
	return _serverName;
}

const std::string
&Config::getHomePage() const
{
	return _homePage;
}

size_t
Config::getClientMaxBodySize() const
{
	return _clientMaxBodySize;
}

const std::vector<Location>
&Config::getLocations() const
{
	return _locations;
}
