/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:04:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/27 17:54:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <map>
# include <iostream>
# include <sstream>

class Response
{
private:
	int									_status;
	std::map<std::string, std::string>	_headers;
	std::string							_body;

public:
	/* --- Orthodox Canonical Form --- */
	Response();
	Response(const Response &copy);
	Response &operator=(const Response &other);
	~Response();

	/* --- Helper Methods --- */
	std::string	getReasonPhrase(int code);

	/* --- Core Methods --- */
	std::string	build();

	/* --- Setters --- */
	void		setStatus(int code);
	void		setHeader(std::string key, std::string value);
	void		setBody(std::string content);
};

#endif