/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/27 16:17:43 by erazumov         ###   ########.fr       */
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

/* ----------------------------- HELPER METHODS ----------------------------- */

void
Request::_handleHeaders()
{
	// 1. Search for the end of the headers (\r\n\r\n) in the entire raw buffer
	size_t	pos = _raw.find("\r\n\r\n");

	if (pos != std::string::npos) // npos means "not found"
	{
		// 2. Mark the boundary where the body starts (after \r\n\r\n)
		_headerSize = pos + 4;
		std::string	headers_part = _raw.substr(0, pos);

		// 3. Pass the str to a specialised parser:
		// parsing AND moving to the next state
		_parseRawHeaders(headers_part);
	}
}

void
Request::_handleBody()
{
	// 1. Calculate the number of body bytes received so far
	// Formula: Total received minus the part used by headers
	size_t	curr_body_size = _raw.size() - _headerSize;

	// 2. Check if the received data matches or exceeds the expected Content-Length
	if (curr_body_size >= _contentLen)
	{
		// 3. It's enough
		// Extract the body from _raw starting at _headerSize
		_body = _raw.substr(_headerSize, _contentLen);
		_state = COMPLETE;
	}
}

void
Request::_parseRawHeaders(const std::string &headers_part)
{
	std::stringstream	ss(headers_part);
	std::string			line;

	// --- 1. PARSE REQUEST-LINE ---
	// Example: "POST /index.html HTTP/1.1"
	if (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		std::stringstream	first_line_ss(line);
		first_line_ss >> _method;  // Extract: POST
		first_line_ss >> _path;    // Extract: /index.html
		first_line_ss >> _version; // Extract: HTTP/1.1
	}

	// --- 2. PARSE HEADER FIELDS ---
	// Example: "Content-Length: 42"
	while (std::getline(ss, line) && line != "\r" && !line.empty())
	{
		if (line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		// Find the colon position to split Key and Value
		size_t	colon = line.find(':');
		if (colon != std::string::npos)
		{
			// Extract Key and Value
			std::string	key = line.substr(0, colon);
			std::string	value = line.substr(colon + 1);

			// Remove the space after the colon if it exists
			size_t		first = value.find_first_not_of(' ');
			if (first != std::string::npos)
				value = value.substr(first);

			_headers[key] = value;
		}
	}

	// --- 3. GET CONTENT-LENGTH ---
	if (_headers.count("Content-Length"))
		_contentLen = std::atoi(_headers["Content-Length"].c_str());
	else
		_contentLen = 0;

	// 5. Decide if to read a body is needed
	if (_method == "POST" && _contentLen > 0)
		_state = READING_BODY;
	else
		_state = COMPLETE;
}

/* ------------------------------ CORE METHODS ------------------------------ */

bool
Request::isComplete()
{
	return _state == COMPLETE;
}

void
Request::addData(std::string chunk)
{
	// SECURITY CHECK: Check if the raw buffer is getting too big
	// _limit comes from the Config (client_max_body_size)
	if (_raw.size() + chunk.size() > _limit)
	{
		_state = ERROR;
		return;
	}

	// 1. Accumulate the incoming data into the raw buffer
	_raw += chunk;

	// 2. Try to find and parse headers
	if (_state == READING_HEADERS)
		_handleHeaders();

	// 3. If the body part is ready, handle it
	if (_state == READING_BODY)
		_handleBody();
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
