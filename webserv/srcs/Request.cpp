/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/25 16:10:36 by erazumov         ###   ########.fr       */
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
	// 1. Create a stream from the raw data to read it line by line
	std::stringstream	ss(raw_data);
	std::string			line;

	// 2. Get only the very first line (the Request line)
	// "GET /index.html HTTP/1.1"
	if (std::getline(ss, line))
	{
		// Remove the '\r' at the end of the line if it exists
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		// 3. Use another stream to split the first line by spaces
		std::stringstream	first_line_ss(line);

		// It skips spaces automatically
		first_line_ss >> _method;  // First word goes to _method
		first_line_ss >> _path;    // Second word to _path
		first_line_ss >> _version; // Third word to _version
	}
	// For debugging
	std::cout << "DEBUG: Method [" << _method << "] Path [" << _path << "]"
			  << std::endl;
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
&Request::getHeaders(const std::string &key) const
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
