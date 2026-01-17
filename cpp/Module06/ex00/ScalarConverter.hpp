/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:25:22 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 15:41:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALAR_CONVERTER_HPP
# define SCALAR_CONVERTER_HPP

# include <iostream>
# include <string>

class ScalarConverter
{
private:
	// --- Orthodox Canonical Form ---
	ScalarConverter();
	ScalarConverter(const ScalarConverter &copy);
	ScalarConverter	&operator=(const ScalarConverter &other);
	~ScalarConverter();

public:
	// --- Member Functions ---
	static void	convert(const std::string &literal);
};

#endif