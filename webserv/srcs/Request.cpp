/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/28 20:46:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Request::Request() :
	_method(""),
	_path(""),
	_version(""),
	_body("")
{
	// std::cout << "Default constructor called" << std::endl;
}

Request::Request(const Request &copy)
{
	*this = copy;
	// std::cout << "Copy constructor called" << std::endl;
}

Request
&Request::operator=(const Request &other)
{
	if (this != &other)
	{
		this->_method = other._method;
		this->_path = other._path;
		this->_version = other._version;
		this->_headers = other._headers;
		this->_body = other._body;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

Request::~Request()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Request::parse(const std::string &raw_data)
{
	std::stringstream	ss(raw_data);
	std::string			line;

	// 1. Parse the first line (Request Line)
	if (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		std::stringstream	first_line_ss(line);
		first_line_ss >> _method;  // First word goes to _method
		first_line_ss >> _path;    // Second word to _path
		first_line_ss >> _version; // Third word to _version
	}

	// 2. Parse all following lines (Headers)
	while (std::getline(ss, line))
	{
		// Remove \r to handle CRLF properly
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		// An empty line means the end of headers
		if (line.empty())
			break;

		// 3. Find the colon to split Key and Value
		size_t	colonPos = line.find(':');
		if (colonPos != std::string::npos)
		{
			// Extract Key and Value
			std::string	key = line.substr(0, colonPos);
			std::string	value = line.substr(colonPos + 1);

			// Trim them and store in the map member variable '_headers'
			_headers[Utils::trim(key)] = Utils::trim(value);
		}
	}
	// --- Body Parsing ---
	// 1. Get the string value of Content-Length
	std::string	lenStr = getHeader("Content-Length");

	if (!lenStr.empty())
	{
		// 2. Convert str to int
		size_t				len = 0;
		std::stringstream	ss_len(lenStr);
		ss_len >> len;

		// 3. Read exactly 'len' characters from the remaining stream
		char				c;
		while (len > 0 && ss.get(c))
		{
			_body += c;
			len--;
		}
	}
	// For debugging
	std::cout << "DEBUG: Method [" << _method << "] Path [" << _path << "]"
			  << std::endl;

	// DEBUG: Show if there is a body
	if (!_body.empty())
		std::cout << "DEBUG: Body received [" << _body << "]" << std::endl;

	// --- DEBUG: Print all recovered headers ---
	std::cout << "--- REQUEST HEADERS ---" << std::endl;

	std::map<std::string, std::string>::iterator	it;

	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		std::cout << "[" << it->first << "]: [" << it->second << "]" << std::endl;
	}

	std::cout << "-----------------------" << std::endl;
}

/* -------------------------------- GETTERS --------------------------------- */

const std::string
&Request::getMethod() const
{
	return this->_method;
}

const std::string
&Request::getPath() const
{
	return this->_path;
}

const std::string
&Request::getVersion() const
{
	return this->_version;
}

const std::string
&Request::getHeader(const std::string &key) const
{
	// 1. Create a constant iterator for the map
	std::map<std::string, std::string>::const_iterator	it = _headers.find(key);

	// 2. Check if the key actually exists in the map
	if (it != _headers.end())
	{
		// If found, return the value associated with the key
		return it->second;
	}
	// 3. If not found, we must return an empty string reference
	// Static variable to avoid returning a reference to a tmp object
	static std::string	empty = "";

	return empty;
}

const std::string
&Request::getBody() const
{
	return this->_body;
}
