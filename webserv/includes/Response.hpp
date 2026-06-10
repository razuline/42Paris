/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:04:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/10 13:09:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "HttpStatus.hpp"

# include <iostream>
# include <map>
# include <sstream>
# include <string>

class Response
{
private:
	int									_status;  // HTTP Status Code
	std::map<std::string, std::string>	_headers; // Storage for "Key: Value" headers
	std::string							_body;    // The actual content (HTML/CSS/Image data)

	/* --- Private Internal Helpers --- */
	std::string	_getReasonPhrase(int code);

public:
	/* --- Orthodox Canonical Form --- */
	Response();
	Response(const Response &copy);
	Response	&operator=(const Response &other);
	~Response();

	/* --- Core Methods --- */
	std::string	build();
	void		defaultErrorPage(int code);
	void		clearBodyForHead();

	/* --- Setters / Getters --- */
	int			getStatus() const;
	void		setStatus(int code);
	void		setHeader(std::string key, std::string value);
	void		setBody(std::string body);
};

#endif