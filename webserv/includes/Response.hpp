/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:04:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/27 19:16:43 by erazumov         ###   ########.fr       */
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
	int									_status;  // HTTP Status Code
	std::map<std::string, std::string>	_headers; // Storage for "Key: Value" headers
	std::string							_body;    // The actual content (HTML/CSS/Image data)

	/* --- Internal Helper Methods --- */
	std::string	getReasonPhrase(int code); // Map status code to words

public:
	/* --- Orthodox Canonical Form --- */
	Response();
	Response(const Response &copy);
	Response &operator=(const Response &other);
	~Response();

	/* --- Setters --- */
	void		setStatus(int code);
	void		setHeader(std::string key, std::string value);
	void		setBody(std::string content);

	/* --- Core Methods --- */
	std::string	build(); // Assembles the final HTTP string to be sent via send()
};

#endif