/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:25:11 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:27:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

ScalarConverter::ScalarConverter()
{
	//std::cout << "Default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;

	//std::cout << "Copy constructor called" << std::endl;
}

ScalarConverter
&ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

ScalarConverter::~ScalarConverter()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ---------------------------- PRIVATE HELPERS ----------------------------- */

// Converts the double value to char and prints the result.
// Handles cases where conversion is impossible or non-displayable.
void
ScalarConverter::printChar(double d)
{
	std::cout << "char: ";

	// Check if the value is NaN, Infinity, or outside the valid ASCII range
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "impossible" << std::endl;
	// Check if the character is printable
	else if (!std::isprint(static_cast<int>(d)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
}

// Converts the double value to int and prints the result.
// Checks for overflows or invalid conversions (NaN/Inf).
void
ScalarConverter::printInt(double d)
{
	std::cout << "int: ";

	// Ensure the value fits within the standard integer limits
	if (std::isnan(d) || std::isinf(d) || d < INT_MIN || d > INT_MAX)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(d) << std::endl;
}

// Converts and prints the value as a float with .0f suffix.
void
ScalarConverter::printFloat(double d)
{
	std::cout << "float: ";

	// Use fixed-point notation and set precision to 1 decimal place
	std::cout << std::fixed << std::setprecision(1) << static_cast<float>(d)
			  << "f" << std::endl;
}

// Prints the value as a double with .0 precision
void
ScalarConverter::printDouble(double d)
{
	std::cout << "double: ";
	std::cout << std::fixed << std::setprecision(1) << d << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

// Detects the type of the literal and performs the conversion.
void
ScalarConverter::convert(const std::string &literal)
{
	double	d;
	char	*endPtr = NULL;

	// Detect if the input is a single character literal (e.g., 'a')
	if (literal.length() == 1 && !std::isdigit(literal[0]))
		d = static_cast<double>(literal[0]);
	else
	{
		// Use strtod to handle numbers and pseudo-literals (nan, inf)
		d = std::strtod(literal.c_str(), &endPtr);

		// Validate the input: only allowed if it's a valid number
		// or a float literal ending in 'f'
		if (*endPtr != '\0' && !(*endPtr == 'f' && *(endPtr + 1) == '\0'))
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: nanf" << std::endl;
			std::cout << "double: nan" << std::endl;
			return;
		}
	}
	// Explicitly cast to other scalar types and display results
	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
