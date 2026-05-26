/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:46:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 17:39:08 by erazumov         ###   ########.fr       */
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
	_clientMaxBodySize(1048576)
{
}

Config::Config(const Config &copy) :
	_port(copy._port),
	_serverName(copy._serverName),
	_folderRoot(copy._folderRoot),
	_homePage(copy._homePage),
	_clientMaxBodySize(copy._clientMaxBodySize)
{
}

Config
&Config::operator=(const Config &other)
{
	if (this != &other)
	{
		this->_port = other._port;
		this->_serverName = other._serverName;
		this->_folderRoot = other._folderRoot;
		this->_homePage = other._homePage;
		this->_clientMaxBodySize= other._clientMaxBodySize;
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