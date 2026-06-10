/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:38:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/06/10 14:57:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Location.hpp"
# include "Utils.hpp"

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>

class Config
{
private:
	int						_port;
	std::string				_serverName;
	std::string				_folderRoot;
	std::string				_homePage;
	size_t					_clientMaxBodySize;
	std::vector<Location>	_locations;

public:
	/* --- Orthodox Canonical Form --- */
	Config();
	Config(const Config &copy);
	Config	&operator=(const Config &other);
	~Config();

	/* --- Core Methods --- */
	void	parse(const std::string &filename);

	/* --- Getters --- */
	int							getPort() const;
	const std::string			&getFolderRoot() const;
	const std::string			&getServerName() const;
	const std::string			&getHomePage() const;
	size_t						getClientMaxBodySize() const;
	const std::vector<Location>	&getLocations() const;
};

#endif