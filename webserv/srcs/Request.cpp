/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/04 15:05:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// Standard 8 KB maximum limit for HTTP Request Headers fields
const size_t	Request::HEADERS_SIZE = 8192;

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
	_limit(1000000), // Default 1 Mb fallback
	_errCode(Http::OK)
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

/* ------------------------------ CORE METHODS ------------------------------ */

bool
Request::isComplete()
{
	return _state == COMPLETE;
}

void
Request::addData(std::string chunk)
{
	// Safeguard against malicious or malformed heavy header payload attacks
	if (_state == READING_HEADERS &&
	   (_raw.size() + chunk.size() > Request::HEADERS_SIZE))
	{
		_state = ERROR;
		_errCode = Http::HEADER_FIELDS_TOO_LARGE;
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

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
Request::_handleHeaders()
{
	// Look for the standard HTTP header/body boundary delimiter
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

	// Check if the current payload exceeds the server configuration limits
	if (curr_body_size > _limit)
	{
		_state = ERROR;
		_errCode = Http::PAYLOAD_TOO_LARGE;
		return;
	}

	// Safety check to ensure the payload chunk doesn't overflow Content-Length
	if (curr_body_size > _contentLength)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}

	// Transition state once the complete expected body bytes are received
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

	// --- 1. PARSE REQUEST-LINE (e.g., "GET /index.html HTTP/1.1") ---
	if (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		std::stringstream	first_line_ss(line);
		first_line_ss >> _method;  // Extract: POST
		first_line_ss >> _path;    // Extract: /index.html
		first_line_ss >> _version; // Extract: HTTP/1.1
	}

	// --- 2. PARSE HTTP HEADER FIELDS (e.g., "Host: localhost") ---
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

			// Strip leading spaces from the header field value data
			size_t		first = value.find_first_not_of(' ');
			if (first != std::string::npos)
				value = value.substr(first);

			_headers[key] = value;
		}
	}

	// --- 3. EXTRACT CONTENT-LENGTH METADATA ---
	if (_headers.count("Content-Length"))
		_contentLength = std::atoi(_headers["Content-Length"].c_str());
	else
		_contentLength = 0;

	// Decide if to read a body is needed based on method type and payload markers
	if (_method == "POST" && _contentLength > 0)
		_state = READING_BODY;
	else
		_state = COMPLETE;
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

Request::State
Request::getState() const
{
	return _state;
}

int
Request::getErrCode() const
{
	return _errCode;
}
