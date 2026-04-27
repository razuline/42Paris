/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:23:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/27 16:14:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Response::Response() :
	_status(200),
	_body("")
{
	// std::cout << "Default constructor called" << std::endl;
}

Response::Response(const Response &copy)
{
	*this = copy;
	// std::cout << "Copy constructor called" << std::endl;
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

	// std::cout << "Copy assignment operator called" << std::endl;
}

Response::~Response()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- HELPER METHODS ----------------------------- */

// Converts HTTP status codes into their standard English phrases
std::string
Response::_getReasonPhrase(int code)
{
	switch(code)
	{
		case 200: return "OK";
		case 201: return "Created";
		case 204: return "No Content";
		case 400: return "Bad Request";
		case 403: return "Forbidden";
		case 404: return "Not Found";
		case 405: return "Method Not Allowed";
		case 500: return "Internal Server Error";
		case 505: return "HTTP Version Not Supported";

		default: return "Unknown Status";
	}
}

/* ------------------------------ CORE METHODS ------------------------------ */

/**
 * The "Sandwich" Builder:
 * 1. Status Line (HTTP/1.1 200 OK)
 * 2. Headers (Content-Type: text/html...)
 * 3. Empty Line (\r\n)
 * 4. Body (The file content)
 */
std::string
Response::build()
{
	std::stringstream	ss;

	// 1. Status Line (CRLF is mandatory at the end)
	ss << "HTTP/1.1 " << _status << " " << _getReasonPhrase(_status) << "\r\n";

	// 2. Iterate through the map to add all headers
	std::map<std::string, std::string>::iterator	it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}
	// 3. The Empty Line that separates headers from the body
	ss << "\r\n";

	// 4. Add the actual content
	ss << _body;

	return ss.str();
}

void
Response::defaultErrorPage(int code)
{
	// 1. Set the status code (e.g,, 404)
	this->setStatus(code);

	// 2. Get the word version (e.g., "Not Found")
	std::string	msg = _getReasonPhrase(code);

	// 3. Create a HTML body
	std::stringstream	ss;
	ss << "<html><head><title>" << code << " " << msg << "</title></head>";
	ss << "<body style='text-align:center; font-family:sans-serif; padding-top:100px;'>";
	ss << "<h1 style='font-size: 50px; color: #333;'>" << code << "</h1>";
	ss << "<h2>" << msg << "</h2>";
	ss << "<hr style='width: 50%;'>";
	ss << "<p>webserv/1.0 (42 Paris)</p>";
	ss << "</body></html>";

	// 4. Use a smart setBody to handle Content-Length automatically
	this->setBody(ss.str());

	// 5. Tell the browser it's an HTML page
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

/**
 * Smart Setter:
 * Whenever set the body, it automatically calculates the size
 * and set the 'Content-Length' header for the user.
 */
void
Response::setBody(std::string content)
{
	_body = content;

	std::stringstream	ss;
	ss << _body.size();
	this->setHeader("Content-Length", ss.str());
}
