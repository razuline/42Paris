/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:09:02 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/08 18:37:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>
# include <iostream>
# include <sstream>
# include <cstdlib>

# include "HttpStatus.hpp"
# include "Utils.hpp"

class Request
{
public:
	enum State
	{
		READING_HEADERS,
		READING_BODY,
		COMPLETE,
		ERROR
	};

private:
	std::string							_method;
	std::string							_path;
	std::string							_version;
	std::map<std::string, std::string>	_headers;
	std::string							_body;

	size_t								_headerSize;
	size_t								_contentLength;

	std::string							_raw;
	State								_state;
	size_t								_limit;
	int									_errCode;

	bool								_isChunked;
	long								_currChunkSize;
	size_t								_chunkedBytesProcessed;

	/* --- Private Internal Helpers --- */
	void	_handleHeaders();
	void	_handleBody();
	void	_parseRawHeaders(const std::string &headers_part);

public:
	/* --- Orthodox Canonical Form --- */
	Request();
	Request(const Request &copy);
	Request	&operator=(const Request &other);
	~Request();

	/* --- Core Methods --- */
	bool	isComplete();
	void	addData(std::string chunk);
	void	setLimit(size_t limit);
	void	clearButPreserveLeftover();

	/* --- Getters --- */
	const std::string	&getMethod() const;
	const std::string	&getPath() const;
	const std::string	&getVersion() const;
	const std::string	&getHeader(const std::string &key) const;
	const std::string	&getBody() const;
	State				getState() const;
	int					getErrCode() const;

	static const size_t					HEADERS_SIZE;
};

#endif