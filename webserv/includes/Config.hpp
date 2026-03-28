/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 13:38:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/28 15:18:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <fstream>
# include <iostream>
# include <sstream>

class Config
{
private:
	int			_port;
	std::string	_serverName;
	std::string	_folderRoot;
	std::string	_homePage;

public:
	/* --- Orthodox Canonical Form --- */
	Config();
	Config(const Config &copy);
	Config &operator=(const Config &other);
	~Config();

	/* --- Core Methods --- */
	void	parse(const std::string &filename);

	/* --- Getters --- */
	int					getPort() const;
	const std::string	getFolderRoot() const;
	const std::string	getServerName() const;
	const std::string	getHomePage() const;
};

#endif