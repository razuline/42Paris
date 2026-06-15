/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:33:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/15 19:34:26 by erazumov         ###   ########.fr       */
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
	_errCode(Http::OK),
	_isChunked(false),
	_currChunkSize(-1),
	_chunkedBytesProcessed(0)
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
	_limit(copy._limit),
	_isChunked(copy._isChunked),
	_currChunkSize(copy._currChunkSize),
	_chunkedBytesProcessed(copy._chunkedBytesProcessed)
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

bool
Request::isComplete()
{
	return _state == COMPLETE;
}

void
Request::addData(std::string chunk)
{
	// Check if headers size exceeds standard 8 KB limit
	if (_state == READING_HEADERS && (_raw.size() + chunk.size() > Request::HEADERS_SIZE))
	{
		_state = ERROR;
		_errCode = Http::HEADER_FIELDS_TOO_LARGE;
		return;
	}
	_raw += chunk;

	if (_state == READING_HEADERS)
	{
		_handleHeaders();
		// FIX: Stop processing immediately if headers are malformed (avoids 200 OK bypass)
		if (_state == ERROR)
			return;
	}
	if (_state == READING_BODY)
		_handleBody();
}

void
Request::setLimit(size_t limit)
{
	_limit = limit;
}

void
Request::clearButPreserveLeftover()
{
	size_t	consumed = 0;
	if (_state == COMPLETE)
	{
		if (_isChunked)
			consumed = _chunkedBytesProcessed;
		else
			consumed = _headerSize + _contentLength;
	}
	else
		consumed = _raw.size();

	std::string	leftover = "";
	if (_raw.size() > consumed)
		leftover = _raw.substr(consumed);

	// Clear everything
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
	else if (_raw.find("\n\n") != std::string::npos)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
	}
}

void
Request::_handleBody()
{
	// Stream Context: Standard Content-Length payload accumulation
	if (!_isChunked)
	{
		size_t	curr_body_size = _raw.size() - _headerSize;

		if (curr_body_size > _limit)
		{
			_state = ERROR;
			_errCode = Http::PAYLOAD_TOO_LARGE;
			return;
		}
		if (curr_body_size >= _contentLength)
		{
			_body = _raw.substr(_headerSize, _contentLength);
			_state = COMPLETE;
		}
		return;
	}

	// Stream Context: Dynamic HTTP/1.1 Chunked Transfer Decoding
	if (_chunkedBytesProcessed == 0)
	{
		if (_headerSize == 0)
		{
			_state = ERROR;
			_errCode = Http::INTERNAL_SERVER_ERROR;
			return;
		}
		_chunkedBytesProcessed = _headerSize;
	}

	while (_state == READING_BODY)
	{
		if (_currChunkSize == -1)
		{
			size_t	crlf_pos = _raw.find("\r\n", _chunkedBytesProcessed);
			if (crlf_pos == std::string::npos)
				break;

			std::string	hexSize = _raw.substr(_chunkedBytesProcessed, crlf_pos - _chunkedBytesProcessed);
			size_t ext_pos = hexSize.find(';');
			if (ext_pos != std::string::npos)
				hexSize = hexSize.substr(0, ext_pos);

			std::stringstream	ss;
			ss << std::hex << hexSize;
			ss >> _currChunkSize;

			if (ss.fail() || _currChunkSize < 0)
			{
				_state = ERROR;
				_errCode = Http::BAD_REQUEST;
				return;
			}
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
			_chunkedBytesProcessed = crlf_pos + 2;
		}
		else
		{
			if (_raw.size() < _chunkedBytesProcessed + _currChunkSize + 2)
				break;

			_body += _raw.substr(_chunkedBytesProcessed, _currChunkSize);

			if (_body.size() > _limit)
			{
				_state = ERROR;
				_errCode = Http::PAYLOAD_TOO_LARGE;
				return;
			}
			_chunkedBytesProcessed += _currChunkSize + 2;
			_currChunkSize = -1;
		}
	}
}

void
Request::_parseRawHeaders(const std::string &headers_part)
{
	size_t	first_crlf = headers_part.find("\r\n");
	if (first_crlf == std::string::npos)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}

	std::string	req_line = headers_part.substr(0, first_crlf);

	size_t	sp1 = req_line.find(' ');
	size_t	sp2 = req_line.find(' ', sp1 + 1);
	if (sp1 == std::string::npos ||
		sp2 == std::string::npos ||
		req_line.find(' ', sp2 + 1) != std::string::npos ||
		req_line.find('\t') != std::string::npos)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}

	_method = req_line.substr(0, sp1);
	_path = req_line.substr(sp1 + 1, sp2 - sp1 - 1);
	_version = req_line.substr(sp2 + 1);

	for (size_t i = 0; i < _method.size(); ++i)
	{
		if (!std::isupper(_method[i]))
		{
			_state = ERROR;
			_errCode = Http::BAD_REQUEST;
			return;
		}
	}

	// Path validation
	if (_path.empty() || _path.size() > 2048 ||
		_path.find('#') != std::string::npos ||
		_path.find('\\') != std::string::npos ||
		_path.find('\0') != std::string::npos)
	{
		_errCode = (_path.size() > 2048)
				  ? Http::HEADER_FIELDS_TOO_LARGE
				  : Http::BAD_REQUEST;
		_state = ERROR;
		return;
	}

	// Version validation
	if (_version != "HTTP/1.1" && _version != "HTTP/1.0")
	{
		_state = ERROR;
		_errCode = (_version == "HTTP/2.0" || _version == "HTTP/3.0")
					? Http::HTTP_VERSION_NOT_SUPPORTED
					: Http::BAD_REQUEST;
		return;
	}

	// Parse headers
	size_t	head_pos = first_crlf + 2;
	size_t	header_count = 0;
	bool	has_host = false;

	while (head_pos < headers_part.size())
	{
		size_t	next_crlf = headers_part.find("\r\n", head_pos);
		if (next_crlf == std::string::npos)
			break;

		std::string	h_line = headers_part.substr(head_pos, next_crlf - head_pos);
		head_pos = next_crlf + 2;

		// Standard CRLF (empty line) marks the end of headers
		if (h_line.empty())
			break;

		size_t	colon = h_line.find(':');
		if (colon == std::string::npos)
			continue; // Skip malformed lines without crashing the request

		std::string	key = h_line.substr(0, colon);
		std::string	value = Utils::trim(h_line.substr(colon + 1));

		// Check for duplicate Host header
		if (key == "Host")
		{
			if (has_host) // Second Host header!
			{
				_state = ERROR;
				_errCode = Http::BAD_REQUEST;
				return;
			}
			has_host = true;

			// Validate Host value
			size_t		p_pos = value.find(':');
			std::string	host_part = (p_pos != std::string::npos)
								   ? value.substr(0, p_pos) : value;
			if (host_part.empty())
			{
				_state = ERROR;
				_errCode = Http::BAD_REQUEST;
				return;
			}
		}

		// Insert header
		_headers[key] = value;
		header_count++;

		if (header_count > 100)
		{
			_state = ERROR;
			_errCode = Http::HEADER_FIELDS_TOO_LARGE;
			return;
		}
	}

	// RFC 7230: HTTP/1.1 requires Host header
	if (_version == "HTTP/1.1" && !has_host)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}

	// Content-Length / Transfer-Encoding validation
	bool	has_cl = _headers.count("Content-Length");
	bool	has_te = _headers.count("Transfer-Encoding");

	if (has_cl && has_te)
	{
		_state = ERROR;
		_errCode = Http::BAD_REQUEST;
		return;
	}
	if (has_te)
	{
		if (_headers["Transfer-Encoding"] != "chunked")
		{
			_state = ERROR;
			_errCode = Http::BAD_REQUEST;
			return;
		}
		_isChunked = true;
		_state = READING_BODY;
	}
	else if (has_cl)
	{
		std::string	cl_val = _headers["Content-Length"];
		if (cl_val.empty())
		{
			_state = ERROR;
			_errCode = Http::BAD_REQUEST;
			return;
		}
		for (size_t i = 0; i < cl_val.size(); ++i)
		{
			if (!std::isdigit(cl_val[i]))
			{
				_state = ERROR;
				_errCode = Http::BAD_REQUEST;
				return;
			}
		}
		_contentLength = std::strtoul(cl_val.c_str(), NULL, 10);
		if (_contentLength > 0)
			_state = READING_BODY;
		else
			_state = COMPLETE;
	}
	else
	{
		// No body expected
		if (_method == "POST" || _method == "PUT")
		{
			_state = ERROR;
			_errCode = Http::BAD_REQUEST;
			return;
		}
		_contentLength = 0;
		_state = COMPLETE;
	}
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

size_t
Request::getRawSize() const
{
	return _raw.size();
}

const std::map<std::string, std::string>
&Request::getHeaders() const
{
	return _headers;
}
