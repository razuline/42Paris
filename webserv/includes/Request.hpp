/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:09:02 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/27 17:21:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include <map>
# include <iostream>
# include <sstream>

class Request
{
private:
	std::string							_method;  // GET, POST, or DELETE
	std::string							_path;    // e.g., /index.html
	std::string							_version; // e.g., HTTP/1.1
	std::map<std::string, std::string>	_headers; // Store all HTTP headers
	std::string							_body;    // For POST requests

public:
	/* --- Orthodox Canonical Form --- */
	Request();
	Request(const Request &copy);
	Request &operator=(const Request &other);
	~Request();

	/* --- Core Methods --- */
	void	parse(const std::string &raw_data);

	/* --- Getters --- */
	const std::string	&getMethod() const;
	const std::string	&getPath() const;
	const std::string	&getVersion() const;
	const std::string	&getHeader(const std::string &key) const;
	const std::string	&getBody() const;
};

#endif