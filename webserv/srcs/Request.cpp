/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 15:16:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

// Standard 8 KB maximum limit for HTTP Request Headers fields
const size_t Request::HEADERS_SIZE = 8192;

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Request::Request() : _method(""),
					 _path(""),
					 _version(""),
					 _body(""),
					 _headerSize(0),
					 _contentLength(0),
					 _raw(""),
					 _state(READING_HEADERS),
					 _limit(1000000), // Default 1 Mb fallback
					 _errCode(Http::OK),
					 _isChunked(false),
					 _currChunkSize(-1),
					 _chunkedBytesProcessed(0)
{
}

Request::Request(const Request &copy) : _method(copy._method),
										_path(copy._path),
										_version(copy._version),
										_headers(copy._headers),
										_body(copy._body),
										_headerSize(copy._headerSize),
										_contentLength(copy._contentLength),
										_raw(copy._raw),
										_state(copy._state),
										_limit(copy._limit),
										_isChunked(copy._isChunked),
										_currChunkSize(copy._currChunkSize),
										_chunkedBytesProcessed(copy._chunkedBytesProcessed)
{
}

Request &Request::operator=(const Request &other)
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
		_isChunked = other._isChunked;
		_currChunkSize = other._currChunkSize;
		_chunkedBytesProcessed = other._chunkedBytesProcessed;
	}
	return *this;
}

Request::~Request()
{
}

/* ------------------------------ CORE METHODS ------------------------------ */

bool Request::isComplete()
{
	return _state == COMPLETE;
}

void Request::addData(std::string chunk)
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

void Request::setLimit(size_t limit)
{
	_limit = limit;
}

void Request::clearButPreserveLeftover()
{
	size_t consumed = 0;
	if (_state == COMPLETE)
	{
		if (_isChunked)
			consumed = _chunkedBytesProcessed;
		else
			consumed = _headerSize + _contentLength;
	}
	else
		consumed = _raw.size();

	std::string leftover = "";
	if (_raw.size() > consumed)
		leftover = _raw.substr(consumed);

	_method.clear();
	_path.clear();
	_version.clear();
	_headers.clear();
	_body.clear();
	_headerSize = 0;
	_contentLength = 0;
	_raw = leftover;
	_state = READING_HEADERS;
	_errCode = Http::OK;
	_isChunked = false;
	_currChunkSize = -1;
	_chunkedBytesProcessed = 0;

	// Automatically parse any leftover pipelined data immediately
	if (!_raw.empty())
	{
		_handleHeaders();
		if (_state == READING_BODY)
			_handleBody();
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void Request::_handleHeaders()
{
	// Look for the standard HTTP header/body boundary delimiter
	size_t pos = _raw.find("\r\n\r\n");

	if (pos != std::string::npos)
	{
		_headerSize = pos + 4;
		std::string headers_part = _raw.substr(0, pos);

		_parseRawHeaders(headers_part);
	}
}

void Request::_handleBody()
{
	// CASE 1: Standard read with Content-Length
	if (!_isChunked)
	{
		size_t curr_body_size = _raw.size() - _headerSize;

		// Check if the current payload exceeds the server configuration limits
		if (curr_body_size > _limit)
		{
			_state = ERROR;
			_errCode = Http::PAYLOAD_TOO_LARGE;
			return;
		}

		// Safety check to ensure the payload chunk doesn't overflow Content-Length
		if (curr_body_size >= _contentLength)
		{
			_body = _raw.substr(_headerSize, _contentLength);
			_state = COMPLETE;
		}

		// Transition state once the complete expected body bytes are received
		if (curr_body_size == _contentLength)
		{
			_body = _raw.substr(_headerSize, _contentLength);
			_state = COMPLETE;
		}
		return;
	}

	// CASE 2: Chunked read (Transfer-Encoding: chunked)
	if (_chunkedBytesProcessed == 0)
	{
		if (_headerSize == 0)
		{
			// If _headerSize isn't defined
			_state = ERROR;
			_errCode = Http::INTERNAL_SERVER_ERROR;
			return;
		}
		_chunkedBytesProcessed = _headerSize;
	}

	while (_state == READING_BODY)
	{
		// A. Look for the chunk size
		if (_currChunkSize == -1)
		{
			size_t crlf_pos = _raw.find("\r\n", _chunkedBytesProcessed);
			if (crlf_pos == std::string::npos)
				break; // Waiting for more data from the socket (non-blocking)

			std::string hexSize = _raw.substr(_chunkedBytesProcessed,
									crlf_pos - _chunkedBytesProcessed);
			std::stringstream ss;
			ss << std::hex << hexSize;
			ss >> _currChunkSize;

			if (ss.fail())
			{
				_state = ERROR;
				_errCode = Http::BAD_REQUEST;
				return;
			}
			// A chunk of size 0 indicates the end of the request
			if (_currChunkSize == 0)
			{
				size_t	final_crlf = _raw.find("\r\n", crlf_pos + 2);
				if (final_crlf != std::string::npos)
				{
					_chunkedBytesProcessed = final_crlf + 2;
					_state = COMPLETE;
				}
				else
					_currChunkSize = -1;
				break;
			}
			_chunkedBytesProcessed = crlf_pos + 2; // Skip the \r\n after the size
		}
		// B. Extract chunk data
		else
		{
			// Check if we received the full chunk + trailing \r\n
			if (_raw.size() < _chunkedBytesProcessed + _currChunkSize + 2)
				break; // Waiting for more data

			// Add pure data to our decoded body
			_body += _raw.substr(_chunkedBytesProcessed, _currChunkSize);

			// Safeguard against oversized payloads
			if (_body.size() > _limit)
			{
				_state = ERROR;
				_errCode = Http::PAYLOAD_TOO_LARGE;
				return;
			}
			_chunkedBytesProcessed += _currChunkSize + 2; // +2 for the \r\n
			_currChunkSize = -1;						  // Reset for the next chunk
		}
	}
}

void Request::_parseRawHeaders(const std::string &headers_part)
{
	std::stringstream	ss(headers_part);
	std::string			line;

	// --- 1. PARSE REQUEST-LINE ---
	while (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		bool	is_blank = true;
		for (size_t i = 0; i < line.size(); ++i)
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				is_blank = false;
				break;
			}
		}
		if (is_blank)
			continue;
		break;
	}

	if (line.empty())
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}

	std::stringstream	first_line_ss(line);
	first_line_ss >> _method;
	first_line_ss >> _path;
	first_line_ss >> _version;

	// --- 2. PARSE FIELDS HEADERS ---
	while (std::getline(ss, line))
	{
		if (!line.empty() && line[line.size() - 1] == '\r')
			line.erase(line.size() - 1);

		if (line.empty()) // Empty boundary line discovered
			break;

		size_t	colon = line.find(':');
		if (colon != std::string::npos)
		{
			// Extract Key and Value
			std::string	key = line.substr(0, colon);
			std::string	value = line.substr(colon + 1);

			// Strip leading spaces from the header field value data
			size_t	first = value.find_first_not_of(' ');
			if (first != std::string::npos)
				value = value.substr(first);

			_headers[key] = value;
		}
	}
	// --- 3. EXTRACT METADATA ---
	if (_headers.count("Transfer-Encoding") &&
		_headers["Transfer-Encoding"].find("chunked") != std::string::npos)
	{
		_isChunked = true;
		_state = READING_BODY;
	}
	else if (_headers.count("Content-Length"))
	{
		_contentLength = std::atoi(_headers["Content-Length"].c_str());
		if (_contentLength > 0)
			_state = READING_BODY;
		else
			_state = COMPLETE;
	}
	else
	{
		_contentLength = 0;
		_state = COMPLETE;
	}
}

/* -------------------------------- GETTERS --------------------------------- */

const std::string &Request::getMethod() const
{
	return _method;
}

const std::string &Request::getPath() const
{
	return _path;
}

const std::string &Request::getVersion() const
{
	return _version;
}

const std::string &Request::getHeader(const std::string &key) const
{
	std::map<std::string, std::string>::const_iterator it = _headers.find(key);

	if (it != _headers.end())
		return it->second;

	static std::string empty = "";
	return empty;
}

const std::string &Request::getBody() const
{
	return _body;
}

Request::State
Request::getState() const
{
	return _state;
}

int Request::getErrCode() const
{
	return _errCode;
}
