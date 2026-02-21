/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:26 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/21 19:35:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>
# include <string>
# include <sstream>
# include <algorithm>

class BitcoinExchange
{
private:
	// Container to store the database (date -> rate)
	// std::map sorts keys automatically, which is perfect for chronological dates
	std::map<std::string, float>	_database;

	/* --- Internal helpers --- */
	bool	isValidDate(const std::string &date) const;
	bool	isValidValue(const std::string &valueStr, float &value) const;

public:
	/* --- Orthodox Canonical Form --- */
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange	&operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	/* --- Core Methods --- */
	bool	loadDatabase(const std::string &filename);
	void	processInput(const std::string &filename);
};

#endif