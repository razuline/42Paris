/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/22 15:29:06 by erazumov         ###   ########.fr       */
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
	*this = copy;

	//std::cout << "Copy constructor called" << std::endl;
}

BitcoinExchange
&BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->_database = other._database;
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

BitcoinExchange::~BitcoinExchange()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- INTERNAL FUNCTIONS --------------------------- */

// Validates date format YYYY-MM-DD and existence
bool
BitcoinExchange::isValidDate(const std::string& date) const
{
	// Check if th format is YYYY-MM-DD (10 characters)
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
		return false;

	// Extract year, month, and day using substr and convert to integers
	int	year = std::atoi(date.substr(0, 4).c_str());
	int	month = std::atoi(date.substr(5, 2).c_str());
	int	day = std::atoi(date.substr(8, 2).c_str());

	// Basic range validation
	if (month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	// Handle February and Leap Years
	if (month == 2)
	{
		bool	leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > (leap ? 29 : 28))
			return false;
	}
	// Handle month with 30 days
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;

	return true;
}

/* ------------------------------ CORE METHODS ------------------------------ */

bool
BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream	file(filename.c_str());

	// Check if the file actually exists and can be opened
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file:" << std::endl;
		return false;
	}

	std::string	line;
	std::getline(file, line); // Skip the header line (date,exchange_rate)

	while (std::getline(file, line))
	{
		size_t	sep = line.find(',');
		if (sep == std::string::npos)
			continue;

		std::string	date = line.substr(0, sep);
		// Convert string to float for the price
		float	rate = static_cast<float>(std::atof(line.substr(sep + 1).c_str()));
		// Store in the map: the date is the key, the rate is the value
		_database[date] = rate;
	}
	file.close();
	return true;
}

void
BitcoinExchange::processInput(const std::string &filename)
{
	std::ifstream	file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string	line;
	// Skip the header line of the input file
	if (!std::getline(file, line))
		return;

	// Critical safety check: Ensure database is not empty to avoid iterator issues
	if (_database.empty())
	{
		std::cerr << "Error: database is empty." << std::endl;
		return;
	}

	while (std::getline(file, line))
	{
		size_t	sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		// Extract and trim the date string
		std::string	date = line.substr(0, sep);
		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}

		// Extract and validate the value associated with the date
		std::string	valStr = line.substr(sep + 1);
		char		*endPtr;
		double		value = std::strtod(valStr.c_str(), &endPtr);

		if (valStr.find_first_not_of(" \t") == std::string::npos
				|| (*endPtr != '\0' && !std::isspace(*endPtr)))
		{
			std::cerr << "Error: bad input => " << valStr << std::endl;
			continue;
		}
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

		// Find the closest date using lower_bound
		// lower_bound returns the first element NOT LESS than the date
		std::map<std::string, float>::iterator	it = _database.lower_bound(date);

		// Case 1: Exact match found or the date is within range
		if (it != _database.end() && it->first == date)
		{
			std::cout << date << " => " << value << " = "
					  << (value * it->second) << std::endl;
		}
		// Case 2: lower_bound returns the very first element, but it's not a match.
		// This means the requested date is older than the oldest date in our database.
		// Decrementing here would cause the Segfault you encountered.
		else if (it == _database.begin())
		{
			std::cerr << "Error: no data for this date => " << date << std::endl;
		}
		// Case 3: Date not found, but we can safely move to the previous available date.
		else
		{
			// If it == _database.end(), the requested date is newer than any entry.
			// If it->first != date, the current 'it' is the first date AFTER the requested one.
			// In both cases, the correct value is the one immediately preceding 'it'.
			--it;
			std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
		}
	}
}
