/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 17:19:21 by erazumov         ###   ########.fr       */
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

bool
BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		return false;
	}

	std::string	line;
	std::getline(file, line); // Skip "date,exchange_rate"

	while (std::getline(file, line))
	{
		size_t	commaPos = line.find(',');
		if (commaPos != std::string::npos)
		{
			std::string	date = line.substr(0, commaPos);
			// Convert string to float for the price
			float	rate = std::atof(line.substr(commaPos + 1).c_str());
			// Store in the map: the date is the key, the rate is the value
			_data[date] = rate;
		}
	}
	return !_data.empty();
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

void
BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
	}

	std::string	line;
	std::getline(file, line); // Skip the header (date | value)

	while (std::getline(file, line))
	{
		size_t	pipePos = line.find('|');
		if (pipePos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string	date = line.substr(0, pipePos);
		// Delete spaces at the end of the date if necessary
		date.erase(date.find_last_not_of(" \t") + 1);

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		// Extract value after the date (before the pipe)
		std::string	valStr = line.substr(pipePos + 1);
		double	value = std::atof(valStr.c_str());

		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		// Search in map
		std::map<std::string, float>::iterator	it = _data.lower_bound(date);

		// If not exact date, move to the previous one
		if (it != _data.end() && it->first == date)
		{
			// Output format: date => value => result
			std::cout << date << " => " << value << " = "
					  << (value * it->second) << std::endl;
		}
		else if (it != _data.begin())
		{
			--it; // Get the most closest date
			std::cout << date << " => " << value << " = "
					  << (value * it->second) << std::endl;
		}
		else
		{
			std::cerr << "Error: date too old." << std::endl;
		}
	}
	file.close();
}
