/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/08 21:21:40 by erazumov         ###   ########.fr       */
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
			waitpid(_pid, NULL, 0);
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
	if (pipe(_pipe_in) == -1 || pipe(_pipe_out) == -1)
	{
		_clearEnv();
		_cleanupPipes();
		return Http::INTERNAL_SERVER_ERROR;
	}
	// 3. Duplicate the current process
	_pid = fork();
	if (_pid < 0)
	{
		// Fork failed: close all open fds and clear memory
		_clearEnv();
		_cleanupPipes();
		return Http::INTERNAL_SERVER_ERROR;
	}
	if (_pid == 0) // CHILD PROCESS
	{
		// Child: Close unused pipe ends
		close(_pipe_in[1]);  // Don't write to stdin pipe
		close(_pipe_out[0]); // Don't read from stdout pipe

		// Redirect stdin/stdout
		dup2(_pipe_in[0], STDIN_FILENO);
		dup2(_pipe_out[1], STDOUT_FILENO);

		// Close original FDs (now duplicated)
		close(_pipe_in[0]);
		close(_pipe_out[1]);

		// Change to script directory
		std::string	target_script = script_path;
		size_t		last_slash = script_path.find_last_of('/');
		if (last_slash != std::string::npos)
		{
			std::string	dir = script_path.substr(0, last_slash);
			chdir(dir.c_str());
			target_script = script_path.substr(last_slash + 1);
		}

		// Prepare arguments for execve
		std::string	exec_path = "./" + target_script;
		char *args[2];
		args[0] = (char *)exec_path.c_str();
		args[1] = NULL;

		// NULL-terminated environment array
		char *const	*envp = &_env[0];  // _env already has NULL at end from _initEnv

		// Execute
		execve(args[0], args, envp);

		// If we get here, execve failed
		std::string	error_msg = "Status: 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n"
								"<html><body><h1>500 CGI Error</h1></body></html>";
		write(STDOUT_FILENO, error_msg.c_str(), error_msg.size());
		exit(1);
	}
	else // PARENT PROCESS
	{
		// Parent: Close unused pipe ends
		close(_pipe_in[0]);  // Don't read from stdin pipe
		close(_pipe_out[1]); // Don't write to stdout pipe

		// Set non-blocking on the ends we keep
		fcntl(_pipe_in[1], F_SETFL, O_NONBLOCK);
		fcntl(_pipe_out[0], F_SETFL, O_NONBLOCK);

		_clearEnv();  // Clean up environment strings (parent doesn't need them)
		return Http::OK;
	}
}

/* ------------------------- PRIVATE INTERNAL HELPERS ----------------------- */

void
CGI::_initEnv(const Request &req, const std::string &script_path)
{
	// Clear any existing environment
	_clearEnv();

	std::stringstream	ss;
	ss << req.getBody().size();

	// Core CGI variables
	_env.push_back(strdup(("REQUEST_METHOD=" + req.getMethod()).c_str()));
	_env.push_back(strdup(("CONTENT_LENGTH=" + ss.str()).c_str()));
	_env.push_back(strdup(("CONTENT_TYPE=" + req.getHeader("Content-Type")).c_str()));
	_env.push_back(strdup("SERVER_PROTOCOL=HTTP/1.1"));
	_env.push_back(strdup("GATEWAY_INTERFACE=CGI/1.1"));
	_env.push_back(strdup(("SCRIPT_FILENAME=" + script_path).c_str()));
	_env.push_back(strdup(("SCRIPT_NAME=" + req.getPath()).c_str()));
	_env.push_back(strdup("REDIRECT_STATUS=200"));

	// Optional headers
	if (!req.getHeader("Cookie").empty())
		_env.push_back(strdup(("HTTP_COOKIE=" + req.getHeader("Cookie")).c_str()));

	if (!req.getHeader("X-Secret-Header-For-Test").empty())
		_env.push_back(strdup(("HTTP_X_SECRET_HEADER_FOR_TEST=" +
							   req.getHeader("X-Secret-Header-For-Test")).c_str()));

	// NULL terminate the array for execve
	_env.push_back(NULL);
}

void
CGI::_clearEnv()
{
	// Free all strings except the NULL terminator
	for (size_t i = 0; i < _env.size(); ++i)
	{
		if (_env[i] != NULL)
			free(_env[i]);  // strdup uses malloc, so free is correct
	}
	_env.clear();  // Vector is now empty
}

void
CGI::_cleanupPipes()
{
	if (_pipe_in[0] != -1)
	{
		close(_pipe_in[0]);
		_pipe_in[0] = -1;
	}
	if (_pipe_in[1] != -1)
	{
		close(_pipe_in[1]);
		_pipe_in[1] = -1;
	}
	if (_pipe_out[0] != -1)
	{
		close(_pipe_out[0]);
		_pipe_out[0] = -1;
	}
	if (_pipe_out[1] != -1)
	{
		close(_pipe_out[1]);
		_pipe_out[1] = -1;
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
