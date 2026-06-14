/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:21:01 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/14 21:38:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <csignal>
# include <ctime>
# include <dirent.h>
# include <iomanip>
# include <iostream>
# include <sstream>
# include <string>
# include <sys/time.h>

namespace Utils
{
	std::string	getMimeType(const std::string& path);
	std::string	trim(const std::string &str);
	std::string	generateAutoindex(const std::string &dirPath, const std::string &reqPath);
	std::string	toStr(int number);

	/* --- LOGS --- */
	#define RESET   "\033[0m"
	#define RED     "\033[31m"
	#define GREEN   "\033[32m"
	#define YELLOW  "\033[33m"
	#define BLUE    "\033[34m"
	#define MAGENTA "\033[35m"
	#define CYAN    "\033[36m"
	#define WHITE   "\033[37m"
	#define BOLD    "\033[1m"

	void	logProgress(int fd, size_t bytesReceived);
	void	clearProgress();
	void	logHeartbeat();
	void	logRequest(const std::string &method, const std::string &path);
	void	logResponse(int statusCode, const std::string &path);
	void	logError(const std::string &message);
	void	logInfo(const std::string &message);
}

#endif