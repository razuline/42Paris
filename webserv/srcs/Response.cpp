/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:23:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/27 19:20:11 by erazumov         ###   ########.fr       */
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
Response::getReasonPhrase(int code)
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
	ss << "HTTP/1.1 " << _status << " " << getReasonPhrase(_status) << "\r\n";

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
