/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/25 17:05:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

CGI::CGI() :
	_env(),
	_pid(-1)
{
	// Initialise all pipe file descriptors to -1 to track their state safely
	_pipe_in[0] = -1;
	_pipe_in[1] = -1;
	_pipe_out[0] = -1;
	_pipe_out[1] = -1;

	// std::cout << "Default constructor called" << std::endl;
}

CGI::~CGI()
{
	// Ensure any open pipe file descriptor is securely closed to prevent FD leaks
	if (_pipe_in[0] != -1)
		close(_pipe_in[0]);
	if (_pipe_in[1] != -1)
		close(_pipe_in[1]);

	if (_pipe_out[0] != -1)
		close(_pipe_out[0]);
	if (_pipe_out[1] != -1)
		close(_pipe_out[1]);

	// Free dynamically allocated memory inside the environment matrix
	_clearEnv();

	// std::cout << "Destructor called" << std::endl;
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
CGI::_initEnv(const Request &req, const std::string &script_path)
{
	// Format HTTP request metadata into standard KEY=VALUE strings
	std::string	line1 = "REQUEST_METHOD=" + req.getMethod();
	std::string	line2 = "CONTENT_LENGTH=" + req.getHeader("Content-Length");

	// Duplicate strings onto the Heap usong strdup for compatibility with execve
	_env.push_back(strdup(line1.c_str()));
	_env.push_back(strdup(line2.c_str()));

	// The env array must be NULL-terminated for execve
	_env.push_back(NULL);
}

void
CGI::_clearEnv()
{
	// Loop through the matrix and free each individual str allocated by strdup
	for (size_t i = 0; i < _env.size(); ++i)
	{
		if (_env[i] != NULL)
			free(_env[i]);
	}
	// Clear the vector container to reset its size back to 0
	_env.clear();
}

/* ------------------------------ CORE METHODS ------------------------------ */

int
CGI::execute(const Request &req, const std::string &script_path)
{
	// 1. Prepare env variables
	_initEnv(req, script_path);

	// 2. Create the input pipe (Server writes body -> CGI script reads it)
	if (pipe(_pipe_in) == -1)
	{
		_clearEnv();
		return 500;
	}
	// 3. Create the output pipe (CGI script writes output -> Server reads it)
	if (pipe(_pipe_out) == -1)
	{
		close(_pipe_in[0]);
		close(_pipe_in[1]);

		_clearEnv();
		return 500;
	}

	// 4. Duplicate the current process
	_pid = fork();
	if (_pid < 0)
	{
		// Fork failed: close all open fds and clear memory
		close(_pipe_in[0]);
		close(_pipe_in[1]);
		close(_pipe_out[0]);
		close(_pipe_out[1]);

		_clearEnv();
		return 500;
	}
	if (_pid == 0) // CHILD PROCESS
	{
		// Redirect script's STDIN to the read end of the input pipe
		dup2(_pipe_in[0], STDIN_FILENO);
		// Redirect script's STDOUT to the write end of the output pipe
		dup2(_pipe_out[1], STDOUT_FILENO);

		// Close original pipe fds as they're now cloned into STDIN/STDOUT
		close(_pipe_in[0]);
		close(_pipe_in[1]);
		close(_pipe_out[0]);
		close(_pipe_out[1]);

		char	*args[3];
		args[0] = (char *)"/usr/bin/python3";   // Path to the interpreter
		args[1] = (char *)script_path.c_str();  // Path to the script target
		args[2] = NULL;                         // Array must be NULL-terminated

		// This replaces the child process memory space entirely
		execve(args[0], args, &_env[0]);
		exit(1);
	}
	else // PARENT PROCESS
	{
		// Close ends of the pipes that are exclusively used by the child process
		close(_pipe_in[0]);
		close(_pipe_out[1]);

		// Non-Blocking mode on
		fcntl(_pipe_in[1], F_SETFL, O_NONBLOCK);
		fcntl(_pipe_out[0], F_SETFL, O_NONBLOCK);

		_clearEnv();
		return 200;
	}
}

/* -------------------------------- GETTERS --------------------------------- */

pid_t
CGI::getPid() const
{
	return _pid;
}

int
CGI::getReadFd() const
{
	return _pipe_out[0]; // 0 is always for reading
}

int
CGI::getWriteFd() const
{
	return _pipe_in[1];  // 1 is always for writing
}
