/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:46:06 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/28 18:39:46 by erazumov         ###   ########.fr       */
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
	_client_max_body_size(1048576)
{
	// std::cout << "Default constructor called" << std::endl;
}

Config::Config(const Config &copy)
{
	*this = copy;
	// std::cout << "Copy constructor called" << std::endl;
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
		this->_client_max_body_size = other._client_max_body_size;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

Config::~Config()
{
	// std::cout << "Destructor called" << std::endl;
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
		std::cerr << "Error: Could not open config file: " << filename << std::endl;
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

		// 3. Skip the empty line
		if (line.empty())
			continue;

		// 4. If NOT empty, look for keywords
		// "listen"
		if (line.find("listen") == 0)
		{
			std::string			value = Utils::trim(line.substr(6));
			std::stringstream	ss(value);
			ss >> _port;
		}
		// "root"
		else if (line.find("root") == 0)
		{
			_folderRoot = Utils::trim(line.substr(4));
		}
		// "server_name"
		else if (line.find("server_name") == 0)
		{
			_serverName = Utils::trim(line.substr(11));
		}
		// "index"
		else if (line.find("index") == 0)
		{
			_homePage = Utils::trim(line.substr(5));
		}
		// "client_max_body_size"
		else if (line.find("client_max_body_size") == 0)
		{
			std::string 		keyword = "client_max_body_size";
			std::string			value = Utils::trim(line.substr(keyword.length()));
			std::stringstream	ss(value);
			ss >> _client_max_body_size;
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
Config::getFolderRoot() const
{
	return _folderRoot;
}

const std::string
Config::getServerName() const
{
	return _serverName;
}

const std::string
Config::getHomePage() const
{
	return _homePage;
}

size_t
Config::getClientMaxBodySize() const
{
	return _client_max_body_size;
}