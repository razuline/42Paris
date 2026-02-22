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
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		return false;
	}

	std::string	line;
	std::getline(file, line); // Skip header

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
	if (!std::getline(file, line)) // Skip header
		return;

	while (std::getline(file, line))
	{
		size_t	sep = line.find('|');
		if (sep == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}

		std::string	date = line.substr(0, sep);
		// Trim spaces autour de la date
		date.erase(date.find_last_not_of(" \t") + 1);
		date.erase(0, date.find_first_not_of(" \t"));

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}


		// Extract value after the date (before the pipe)
		std::string	valStr = line.substr(sep + 1);
		char		*endPtr;
		double		value = std::strtod(valStr.c_str(), &endPtr);

		// Validation of the value
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
		}
		else if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
		}
		else
		{
			// Find the rate using lower_bound
			// lower_bound returns the first element >= date
			std::map<std::string, float>::iterator	it =
					_database.lower_bound(date);

			// If not exact date, move to the previous one
			if (it == _database.end()
					|| (it->first != date && it != _database.begin()))
			{
				if (it->first != date)
					--it; // Move to previous date if not exact match
			}

			if (it == _database.begin() && it->first > date)
			{
				 std::cerr << "Error: no data for this date." << std::endl;
			}
			else
			{
				// Output format: date => value => result
				std::cout << date << " => " << value << " = "
						  << (value * it->second) << std::endl;
			}
		}
	}
}
