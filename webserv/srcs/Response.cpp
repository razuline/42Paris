/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:23:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 13:10:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Response::Response() : _status(Http::OK),
					   _body("")
{
	// setHeader("Server", "webserv/1.0 (42 Paris)");
}

Response::Response(const Response &copy) : _status(copy._status),
										   _headers(copy._headers),
										   _body(copy._body)
{
}

Response &Response::operator=(const Response &other)
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

/* ------------------------------ CORE METHODS ------------------------------ */

std::string
Response::build()
{
	std::stringstream	ss;

	// 1. Build HTTP Protocol Status Line (e.g., HTTP/1.1 200 OK\r\n)
	ss << "HTTP/1.1 " << _status << " " << _getReasonPhrase(_status) << "\r\n";
	ss << "Server: " << "webserv/1.0 (42 Paris)" << "\r\n";

	// 2. Append all custom standard map-mapped headers to the stream
	std::map<std::string, std::string>::iterator	it;
	for (it = _headers.begin(); it != _headers.end(); ++it)
	{
		ss << it->first << ": " << it->second << "\r\n";
	}

	// 3. Mandatory empty line boundary
	ss << "\r\n";

	// 4. Append the final payload body data
	ss << _body;

	return ss.str();
}

void Response::defaultErrorPage(int code)
{
	setStatus(code);
	setHeader("Content-Type", "text/html");

	std::string			phrase = _getReasonPhrase(code);
	std::stringstream	ss;
	ss << code;
	std::string			codeStr = ss.str();

	std::string			body =
		"<html><head><title>" + codeStr + " " + phrase + "</title></head>"
		"<body style='background-color: #0f172a; color: #f8fafc; font-family: sans-serif; display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0;'>"
		"<div style='text-align: center;'>"
		"<h1 style='font-size: 80px; margin: 0; color: #38bdf8; font-weight: 800; letter-spacing: -2px;'>" +
		codeStr + "</h1>"
		"<p style='font-size: 20px; color: #94a3b8; margin: 10px 0 0 0; text-transform: uppercase; letter-spacing: 1px;'>" +
		phrase + "</p>"
		"<hr style='border: 0; border-top: 1px solid #334155; width: 50px; margin: 30px auto;'>"
		"<p style='font-size: 12px; color: #475569;'>webserv/1.0 (42 Paris)</p>"
		"</div>"
		"</body></html>";

	setBody(body);  // This will set Content-Length automatically
}

void
Response::clearBodyForHead()
{
	_body.clear();
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

std::string
Response::_getReasonPhrase(int code)
{
	switch (code)
	{
	// 1xx & 2xx Codes
	case Http::OK:
		return "OK"; // 200
	case Http::CREATED:
		return "Created"; // 201
	case Http::ACCEPTED:
		return "Accepted"; // 202
	case Http::NO_CONTENT:
		return "No Content"; // 204

	// 3xx Codes
	case Http::MOVED_PERMANENTLY:
		return "Moved Permanently"; // 301
	case Http::FOUND:
		return "Found"; // 302

	// 4xx Codes
	case Http::BAD_REQUEST:
		return "Bad Request"; // 400
	case Http::UNAUTHORIZED:
		return "Unauthorized"; // 401
	case Http::FORBIDDEN:
		return "Forbidden"; // 403
	case Http::NOT_FOUND:
		return "Not Found"; // 404
	case Http::METHOD_NOT_ALLOWED:
		return "Method Not Allowed"; // 405
	case Http::PAYLOAD_TOO_LARGE:
		return "Payload Too Large"; // 413
	case Http::IM_A_TEAPOT:
		return "I'm a teapot"; // 418 🫖
	case Http::HEADER_FIELDS_TOO_LARGE:
		return "Request Header Fields Too Large"; // 431

	// 5xx Codes
	case Http::INTERNAL_SERVER_ERROR:
		return "Internal Server Error"; // 500
	case Http::BAD_GATEWAY:
		return "Bad Gateway"; // 502
	case Http::SERVICE_UNAVAILABLE:
		return "Service Unavailable"; // 503
	case Http::HTTP_VERSION_NOT_SUPPORTED:
		return "HTTP Version Not Supported"; // 505

	default:
		return "Unknown Status";
	}
}

/* --------------------------- SETTERS / GETTERS ---------------------------- */

int
Response::getStatus() const
{
	return _status;
}

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

	// Only set Content-Length if not a redirect or special status
	if (_status != Http::NO_CONTENT &&
		(_status < 300 || _status >= 400) &&
		_status != Http::NOT_MODIFIED)
	{
		std::stringstream ss;
		ss << _body.size();
		setHeader("Content-Length", ss.str());
	}
	else
	{
		// For 204, 304, and 3xx, Content-Length should be 0
		setHeader("Content-Length", "0");
	}
}
