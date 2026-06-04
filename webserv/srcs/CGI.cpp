/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/04 16:33:52 by erazumov         ###   ########.fr       */
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

	// Reap the child process to prevent zombie process leaks
	if (_pid > 0)
	{
		int	status;

		if (waitpid(_pid, &status, WNOHANG) == 0)
		{
			kill(_pid, SIGKILL);
			waitpid(_pid, NULL, 0); // On récolte le zombie proprement
		}
	}

	// Free dynamically allocated memory inside the environment matrix
	_clearEnv();
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
		return Http::INTERNAL_SERVER_ERROR;
	}
	// 3. Create the output pipe (CGI script writes output -> Server reads it)
	if (pipe(_pipe_out) == -1)
	{
		close(_pipe_in[0]);
		close(_pipe_in[1]);

		_clearEnv();
		return Http::INTERNAL_SERVER_ERROR;
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
		return Http::INTERNAL_SERVER_ERROR;
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

		std::string		target_script = script_path;
		size_t			last_slash = script_path.find_last_of('/');

		if (last_slash != std::string::npos)
		{
			std::string	dir = script_path.substr(0, last_slash);
			chdir(dir.c_str());
			target_script = script_path.substr(last_slash + 1);
		}

		// NATIVE SHEBANG EXECUTION
		// Construct the execution path relative to the new working directory
		std::string		exec_path = "./" + target_script;

		char	*args[2];
		args[0] = (char *)exec_path.c_str(); // The OS kernel will parse the shebang line natively
		args[1] = NULL; // Array must be NULL-terminated

		// Execute the script directly
		execve(args[0], args, &_env[0]);
		exit(1); // If execve fails (e.g., script is not executable or shebang is malformed)
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
		return Http::OK;
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
CGI::_initEnv(const Request &req, const std::string &script_path)
{
	// Core CGI/1.1 variables required by both Python and especially PHP
	std::string	line1 = "REQUEST_METHOD=" + req.getMethod();
	std::string	line2 = "CONTENT_LENGTH=" + req.getHeader("Content-Length");

	std::string	line3 = "CONTENT_TYPE=" + req.getHeader("Content-Type");

	std::string	line4 = "SERVER_PROTOCOL=HTTP/1.1";
	std::string	line5 = "GATEWAY_INTERFACE=CGI/1.1";
	std::string	line6 = "SCRIPT_FILENAME=" + script_path; // Absolute path to target script
	std::string	line7 = "SCRIPT_NAME=" + req.getPath();
	// PHP-cgi strictly requires this variable to security-check the execution
	std::string	line8 = "REDIRECT_STATUS=200";

	// Duplicate strings onto the Heap usong strdup for compatibility with execve
	_env.push_back(strdup(line1.c_str()));
	_env.push_back(strdup(line2.c_str()));
	_env.push_back(strdup(line3.c_str()));
	_env.push_back(strdup(line4.c_str()));
	_env.push_back(strdup(line5.c_str()));
	_env.push_back(strdup(line6.c_str()));
	_env.push_back(strdup(line7.c_str()));
	_env.push_back(strdup(line8.c_str()));

	// Forward Cookies if they exist in request
	if (!req.getHeader("Cookie").empty())
	{
		std::string	cookie_line = "HTTP_COOKIE=" + req.getHeader("Cookie");
		_env.push_back(strdup(cookie_line.c_str()));
	}

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
