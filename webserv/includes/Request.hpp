/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:09:02 by erazumov          #+#    #+#             */
/*   Updated: 2026/04/27 16:12:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>
# include <iostream>
# include <sstream>

# include "Utils.hpp"

class Request
{
public:
	// Definition of the different stages of HTTP request parsing
	enum	RequestState
	{
		READING_HEADERS, // Searching for the end os the headers (\r\n\r\n)
		READING_BODY,    // Headers found, waiting for the body based on Content-Length
		COMPLETE,        // Request is fully received and parsed
		ERROR            // An error occurred during parsing
	};

private:
	std::string							_method;     // GET, POST, or DELETE
	std::string							_path;       // e.g., /index.html
	std::string							_version;    // e.g., HTTP/1.1
	std::map<std::string, std::string>	_headers;    // Store all HTTP headers
	std::string							_body;       // For POST requests

	size_t								_headerSize; // Store the boundary bw headers and body
	size_t								_contentLen; // Store the expected body size

	// Buffer to store raw data chunks received from the client
	std::string							_raw;
	// Current state of the request parsing process
	RequestState						_state;

	/* --- Private Internal Helpers --- */
	void	_handleHeaders();
	void	_handleBody();
	void	_parseRawHeaders(const std::string &headers_part);

public:
	/* --- Orthodox Canonical Form --- */
	Request();
	Request(const Request &copy);
	Request &operator=(const Request &other);
	~Request();

	/* --- Core Methods --- */
	// Checks if the request has reached the COMPLETE state
	bool	isComplete();
	// Adds a new chunk of data received from the socket to the internal buffer
	void	addData(std::string chunk);

	/* --- Getters --- */
	const std::string	&getMethod() const;
	const std::string	&getPath() const;
	const std::string	&getVersion() const;
	const std::string	&getHeader(const std::string &key) const;
	const std::string	&getBody() const;
};

#endif