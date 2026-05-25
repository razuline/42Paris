/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 13:39:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

CGI::CGI() :
	_env(),
	_pid(-1)
{
	_pipe_in[0] = -1;
	_pipe_in[1] = -1;
	_pipe_out[0] = -1;
	_pipe_out[1] = -1;

	// std::cout << "Default constructor called" << std::endl;
}

CGI::~CGI()
{
	if (_pipe_in[0] != -1)
		close(_pipe_in[0]);
	if (_pipe_in[1] != -1)
		close(_pipe_in[1]);

	if (_pipe_out[0] != -1)
		close(_pipe_out[0]);
	if (_pipe_out[1] != -1)
		close(_pipe_out[1]);
	_clearEnv();

	// std::cout << "Destructor called" << std::endl;
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
CGI::_initEnv(const Request &req, const std::string &script_path)
{
	std::string	line1 = "REQUEST_METHOD=" + req.getMethod();
	std::string	line2 = "CONTENT_LENGTH=" + req.getHeader("Content-Length");

	_env.push_back(strdup(line1.c_str()));
	_env.push_back(strdup(line2.c_str()));

	_env.push_back(NULL);
}