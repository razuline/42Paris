/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:46:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/15 18:56:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

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

std::vector<Config>
Config::parseFile(const std::string &filename)
{
	std::vector<Config>	configs;
	std::ifstream		file(filename.c_str());
	std::string			line;

	if (!file.is_open())
	{
		std::cerr << "[Config] Error: Cannot open config file "
				  << filename << std::endl;
		return configs;
	}

	Config	currConfig;
	bool	inServer = false;

	while (std::getline(file, line))
	{
		size_t	commentPos = line.find("#");
		if (commentPos != std::string::npos)
			line.erase(commentPos);

		line = Utils::trim(line);
		if (line.empty())
			continue;

		if (line == "server" || (line.find("server") == 0 &&
			line.find("{") != std::string::npos))
		{
			if (inServer)
				configs.push_back(currConfig);
			currConfig = Config(); // Reset to defaults for next context
			inServer = true;
			continue;
		}
		if (!inServer)
			continue;
		if (line == "}")
		{
			configs.push_back(currConfig);
			inServer = false;
			continue;
		}
		if (line.find("listen") == 0)
		{
			std::string			value = Utils::trim(line.substr(6));
			size_t				colon_pos = value.find_last_of(':');
			if (colon_pos != std::string::npos)
				value = value.substr(colon_pos + 1);

			std::stringstream	ss(value);
			int					port = 8080;
			ss >> port;
			currConfig._port = port;
		}
		else if (line.find("root") == 0)
			currConfig._folderRoot = Utils::trim(line.substr(4));
		else if (line.find("server_name") == 0)
			currConfig._serverName = Utils::trim(line.substr(11));
		else if (line.find("index") == 0)
			currConfig._homePage = Utils::trim(line.substr(5));
		else if (line.find("client_max_body_size") == 0)
		{
			std::string			value = Utils::trim(line.substr(20));
			std::stringstream	ss(value);
			size_t				maxSize = 0;
			ss >> maxSize;
			currConfig._clientMaxBodySize = maxSize;
		}
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
				// FIX: Support the 'cgi_extension .py /usr/bin/python3' format
				else if (line.find("cgi_extension") == 0)
				{
					std::string			cgi_line = Utils::trim(line.substr(13));
					std::stringstream	css(cgi_line);
					std::string			ext, binary;
					css >> ext >> binary;

					// Inject a virtual extension location block for exact extension matching
					Location	cgiLoc = loc;
					cgiLoc.setPath(ext);
					cgiLoc.setCgiPath(binary);
					currConfig._locations.push_back(cgiLoc);
				}
				// FIX: Support both 'allow_methods' and 'allowed_methods' variations
				else if (line.find("allow_methods") == 0 ||
						 line.find("allowed_methods") == 0)
				{
					std::vector<std::string>	methods;
					size_t	keyword_len = (line.find("allowed_methods") == 0) ? 15 : 13;
					std::stringstream	mss(Utils::trim(line.substr(keyword_len)));
					std::string			methodToken;
					while (mss >> methodToken)
						methods.push_back(methodToken);
					loc.setMethods(methods);
				}
			}
			currConfig._locations.push_back(loc);
		}
	}
	file.close();
	return configs;
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
