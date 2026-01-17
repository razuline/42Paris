/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:25:22 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:10:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <climits>
# include <cmath>
# include <cstdlib>
# include <iomanip>
# include <iostream>
# include <limits>
# include <string>

class ScalarConverter
{
private:
	// Private to prevent instantiation
	// --- Orthodox Canonical Form ---
	ScalarConverter();
	ScalarConverter(const ScalarConverter &copy);
	ScalarConverter	&operator=(const ScalarConverter &other);
	~ScalarConverter();

	/* --- Private Helper Functions for Output --- */
	static void	printChar(double d);
	static void	printInt(double d);
	static void	printFloat(double d);
	static void	printDouble(double d);

public:
	// --- Mandatory Static Method ---
	static void	convert(const std::string &literal);
};

#endif