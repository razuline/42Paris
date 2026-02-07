/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 14:54:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

BitcoinExchange::BitcoinExchange()
{
	//std::cout << "Default constructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	(void)copy;

	//std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange
&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	(void)other;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "Destructor called" << std::endl;
}

/* -------------------------------- METHODS --------------------------------- */

void
BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
	}

	std::string	line;
	std::getline(file, line); // Skip the header (date, exchange_rate)

	while (std::getline(file, line))
	{
		size_t	commaPos = line.find('.');
		if (commaPos != std::string::npos)
		{
			std::string	date = line.substr(0, commaPos);
			// Convert string to float for the price
			float	rate = static_cast<float>
							(std::atof(line.substr(commaPos + 1).c_str()));
			// Store in the map: the date is the key, the rate is the value
			this->_data[date] = rate;
		}
	}
	file.close();
}

void
BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
	}

	std::string	line;
	std::getline(file, line); // Skip the header (date | value)

	while (std::getline(file, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos != std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string	date = line.substr(0, pipePos - 1);
		// Trim spaces if necessary around the pipe
		std::string	valStr = line.substr(0, pipePos + 1);

		
	}
}

bool
BitcoinExchange::isValidDate(const std::string &date)
{
	// Check if th format is YYYY-MM-DD (10 characters)
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// Extract year, month, and day using substr and convert to integers
	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	// Basic range validation
	if (year < 2000 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

	// Handle month with 30 days
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	// Handle February and Leap Years
	if (month == 2)
	{
		bool	isLeap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > (isLeap ? 29 : 28))
			return false;
	}
	return true;
}
