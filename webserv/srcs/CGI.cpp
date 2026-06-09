/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/09 17:12:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

#include <cstdio>

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
CGI::execute(const Request &req, const std::string &script_path,
				const std::string &cgi_path)
{
	// 1. Prepare env variables
	_initEnv(req, script_path);

	std::string	abs_cgi_path = cgi_path;
	if (!abs_cgi_path.empty() && abs_cgi_path[0] != '/')
	{
		char	cwd[4096];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			if (abs_cgi_path.find("./") == 0)
				abs_cgi_path = abs_cgi_path.substr(2);
			abs_cgi_path = std::string(cwd) + "/" + abs_cgi_path;
		}
	}

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
		_clearEnv();
		_cleanupPipes();
		return Http::INTERNAL_SERVER_ERROR;
	}
	if (_pid == 0) // CHILD PROCESS
	{
		// Child: Close unused pipe ends
		close(_pipe_in[1]);
		close(_pipe_out[0]);

		// Redirect stdin/stdout
		dup2(_pipe_in[0], STDIN_FILENO);
		dup2(_pipe_out[1], STDOUT_FILENO);

		// Close original FDs
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
		char	*args[3];
		args[0] = (char *)abs_cgi_path.c_str();
		args[1] = (char *)target_script.c_str();  // Le script ciblé
		args[2] = NULL;

		// NULL-terminated environment array (re-déclaré explicitement ici)
		char *const	*envp = &_env[0];

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
		close(_pipe_in[0]);
		close(_pipe_out[1]);

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
	// Core CGI variables
	_env.push_back(strdup(("REQUEST_METHOD=" + req.getMethod()).c_str()));
	_env.push_back(strdup("SERVER_PROTOCOL=HTTP/1.1"));
	_env.push_back(strdup("GATEWAY_INTERFACE=CGI/1.1"));
	_env.push_back(strdup("SERVER_PORT=8080"));
	_env.push_back(strdup("SERVER_SOFTWARE=webserv/1.0"));
	_env.push_back(strdup("SERVER_NAME=localhost"));
	_env.push_back(strdup(("SCRIPT_FILENAME=" + script_path).c_str()));
	_env.push_back(strdup(("SCRIPT_NAME=" + req.getPath()).c_str()));
	_env.push_back(strdup("REDIRECT_STATUS=200"));
	_env.push_back(strdup(("PATH_INFO=" + req.getPath()).c_str()));
	_env.push_back(strdup(("PATH_TRANSLATED=" + script_path).c_str()));

	// CONTENT_LENGTH
	std::stringstream ss;
	ss << req.getBody().size();
	_env.push_back(strdup(("CONTENT_LENGTH=" + ss.str()).c_str()));

	// CONTENT_TYPE
	std::string contentType = req.getHeader("Content-Type");
	if (!contentType.empty())
		_env.push_back(strdup(("CONTENT_TYPE=" + contentType).c_str()));

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
