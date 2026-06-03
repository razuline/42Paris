/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:23:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/03 16:00:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Response::Response() :
	_status(SC_200),
	_body("")
{
	setHeader("Server", "webserv/1.0 (42 Paris)");
}

Response::Response(const Response &copy) :
	_status(copy._status),
	_headers(copy._headers),
	_body(copy._body)
{
}

Response
&Response::operator=(const Response &other)
{
	if (this != &other)
	{
		this->_status = other._status;
		this->_headers = other._headers;
		this->_body = other._body;
	}
	return *this;
}

Response::~Response()
{
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

std::string
Response::_getReasonPhrase(int code)
{
	switch(code)
	{
		case SC_200: return "OK";
		case SC_201: return "Created";
		case SC_202: return "Accepted";
		case SC_204: return "No Content";
		case SC_301: return "Moved Permanently";
		case SC_302: return "Found";
		case SC_400: return "Bad Request";
		case SC_401: return "Unauthorized";
		case SC_403: return "Forbidden";
		case SC_404: return "Not Found";
		case SC_405: return "Method Not Allowed";
		case SC_413: return "Payload Too Large";
		case SC_431: return "Request Header Fields Too Large";
		case SC_500: return "Internal Server Error";
		case SC_502: return "Bad Gateway";
		case SC_503: return "Service Unavailable";
		case SC_505: return "HTTP Version Not Supported";

		default:     return "Unknown Status";
	}
}

/* ------------------------------ CORE METHODS ------------------------------ */

std::string
Response::build()
{
	std::stringstream	ss;

	// 1. Build HTTP Protocol Status Line (e.g., HTTP/1.1 200 OK\r\n)
	ss << "HTTP/1.1 " << _status << " " << _getReasonPhrase(_status) << "\r\n";

	// 2. Append all custom standard map-mapped headers to the stream
	std::map<std::string, std::string>::iterator	it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}

	// 3. Inject mandatory empty boundary line separating headers and payload body data
	ss << "\r\n";

	// 4. Append the final payload body data
	ss << _body;

	return ss.str();
}

void
Response::defaultErrorPage(int code)
{
	setStatus(code);
	std::string			msg = _getReasonPhrase(code);

	// Create a beautifully aligned boilerplate error document stringstream
	std::stringstream	ss;
	ss << "<html><head><title>" << code << " " << msg << "</title></head>";
	ss << "<body style='text-align:center; font-family:sans-serif; padding-top:100px;'>";
	ss << "<h1 style='font-size: 50px; color: #333;'>" << code << "</h1>";
	ss << "<h2>" << msg << "</h2>";
	ss << "<hr style='width: 50%;'>";
	ss << "<p>webserv/1.0 (42 Paris)</p>";
	ss << "</body></html>";

	// Commits the structure (Content-Length metadata auto-injects inside setBody)
	this->setBody(ss.str());
	this->setHeader("Content-Type", "text/html");
}

/* -------------------------------- SETTERS --------------------------------- */

void
Response::setStatus(int code)
{
	_status = code;
}

void
Response::setHeader(std::string key, std::string value)
{
	_headers[key] = value;
}

void
Response::setBody(std::string body)
{
	_body = body;

	// SMART ENCAPSULATION: Automatically tracks and sets Content-Length metadata
	std::stringstream	ss;
	ss << _body.size();
	setHeader("Content-Length", ss.str());
}
