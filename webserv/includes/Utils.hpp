/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 19:21:01 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/26 19:18:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>
# include <dirent.h>

namespace Utils
{
	std::string	getMimeType(const std::string& path);
	std::string	trim(const std::string &str);
	std::string	generateAutoindex(const std::string &dirPath, const std::string &reqPath);
}

#endif