/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/02 20:37:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

//const size_t	Request::HEADERS_SIZE = 8192;
const size_t	Request::HEADERS_SIZE = 1024;

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Request::Request() :
	_method(""),
	_path(""),
	_version(""),
	_body(""),
	_headerSize(0),
	_contentLength(0),
	_raw(""),
	_state(READING_HEADERS),
	_limit(1000000) // 1 Mb
{
}

Request::Request(const Request &copy) :
	_method(copy._method),
	_path(copy._path),
	_version(copy._version),
	_headers(copy._headers),
	_body(copy._body),
	_headerSize(copy._headerSize),
	_contentLength(copy._contentLength),
	_raw(copy._raw),
	_state(copy._state),
	_limit(copy._limit)
{
}

Request
&Request::operator=(const Request &other)
{
	if (this != &other)
	{
		_method = other._method;
		_path = other._path;
		_version = other._version;
		_headers = other._headers;
		_body = other._body;
		_headerSize = other._headerSize;
		_contentLength = other._contentLength;
		_raw = other._raw;
		_state = other._state;
		_limit = other._limit;
	}
	return *this;
}

Request::~Request()
{
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Request::_handleHeaders()
{
	size_t	pos = _raw.find("\r\n\r\n");

	if (pos != std::string::npos)
	{
		_headerSize = pos + 4;
		std::string	headers_part = _raw.substr(0, pos);

		_parseRawHeaders(headers_part);
	}
}

void
Request::_handleBody()
{
	size_t	curr_body_size = _raw.size() - _headerSize;

	if (curr_body_size > _limit) {
		_state = ERROR;
		_errCode = 413;
		return;
	}

	if (curr_body_size > _contentLength) {
		_state = ERROR;
		_errCode = 400;
		return;
	}

	if (curr_body_size == _contentLength)
	{
		_body = _raw.substr(_headerSize, _contentLength);
		_state = COMPLETE;
	}
}

void
Request::_parseRawHeaders(const std::string &headers_part)
{
	std::stringstream		ss(headers_part);
	std::string				line;

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
		_contentLength = std::atoi(_headers["Content-Length"].c_str());
	else
		_contentLength = 0;

	// Decide if to read a body is needed
	if (_method == "POST" && _contentLength > 0)
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

	if (_raw.size() + chunk.size() > Request::HEADERS_SIZE)
	{
		_state = ERROR;
		_errCode = 431;
		return;
	}

	_raw += chunk;

	if (_state == READING_HEADERS)
		_handleHeaders();

	if (_state == READING_BODY)
		_handleBody();
}

void
Request::setLimit(size_t limit)
{
	_limit = limit;
}

/* -------------------------------- GETTERS --------------------------------- */

const std::string
&Request::getMethod() const
{
	return _method;
}

const std::string
&Request::getPath() const
{
	return _path;
}

const std::string
&Request::getVersion() const
{
	return _version;
}

const std::string
&Request::getHeader(const std::string &key) const
{
	std::map<std::string, std::string>::const_iterator	it = _headers.find(key);

	if (it != _headers.end())
		return it->second;

	static std::string	empty = "";
	return empty;
}

const std::string
&Request::getBody() const
{
	return _body;
}

RequestState
Request::getState() const
{
	return _state;
}

int
Request::getErrCode() const
{
	return _errCode;
}
