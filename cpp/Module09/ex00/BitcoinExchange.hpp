/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:26 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 14:53:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <map>

class BitcoinExchange
{
private:
	// map<key_type, value_type> map_name;
	std::map<std::string, float>	_data;

public:
	/* --- Orthodox Canonical Form --- */
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange &copy);
	BitcoinExchange	&operator=(const BitcoinExchange &other);
	~BitcoinExchange();

	/* --- Methods --- */
	void	loadDatabase(const std::string &filename);
	void	processInput(const std::string &filename);
	bool	isValidDate(const std::string &date);
};

#endif