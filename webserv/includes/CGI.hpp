/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:54:31 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 16:22:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include <string>
# include <vector>
# include <map>
# include <cstring>
# include <cstdlib>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>

# include "Request.hpp"

class CGI
{
private:
	std::vector<char *>	_env;          // Environment array for execve()
	pid_t				_pid;          // Child process ID
	int					_pipe_in[2];   // Server writes request body here
	int					_pipe_out[2];  // Server reads CGI response from here

	/* --- Copy Blockade --- */ // (prevents double-closing system pipes)
	CGI(const CGI &copy);
	CGI		&operator=(const CGI &other);

	/* --- Private Internal Helpers --- */
	void	_initEnv(const Request &req, const std::string &script_path);
	void	_clearEnv();

public:
	/* --- Orthodox Canonical Form --- */
	CGI();
	~CGI();

	/* --- Core Methods --- */
	int		execute(const Request &req, const std::string &script_path);

	/* --- Getters --- */
	pid_t	getPid() const;
	int		getReadFd() const;
	int		getWriteFd() const;
};

#endif