/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:31 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/12 12:52:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "HttpStatus.hpp"
# include "Request.hpp"

# include <cstdlib>
# include <cstdio>
# include <cstring>
# include <fcntl.h>
# include <map>
# include <signal.h>
# include <string>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <vector>

class CGI
{
private:
	std::vector<char *>	_env;          // Environment array for execve()
	pid_t				_pid;          // Child process ID
	int					_pipe_in[2];   // Server writes request body here
	int					_pipe_out[2];  // Server reads CGI response from here

	/* --- Private Internal Helpers --- */
	void	_initEnv(const Request &req, const std::string &script_path,
					 const std::string &port);
	void	_clearEnv();
	void	_cleanupPipes();

	/* --- Copy Blockade --- */ // (prevents double-closing system pipes)
	CGI(const CGI &copy);
	CGI		&operator=(const CGI &other);

public:
	/* --- Orthodox Canonical Form --- */
	CGI();
	~CGI();

	/* --- Core Methods --- */
	int		execute(const Request &req, const std::string &script_path,
					const std::string &cgi_path, const std::string &port);

	/* --- Getters --- */
	pid_t	getPid() const;
	int		getReadFd() const;
	int		getWriteFd() const;
};

#endif