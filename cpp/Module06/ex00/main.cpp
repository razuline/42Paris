/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:28:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:31:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

#include <vector>

int	main(int ac, char **av)
{
	// If an argument is provided, run the conversion on it
	if (ac == 2)
	{
		ScalarConverter::convert(av[1]);
		return 0;
	}
	// Otherwise, run a suite of automated tests to verify requirements
	std::cout << "--- SELF-TESTING MODE ---" << std::endl;

	std::string tests[] =
	{
		"0",          // int / double / float
		"nan",        // double pseudo-literal
		"42.0f",      // float literal
		"a",          // char literal
		"42",         // simple int
		"-inff",      // float pseudo-literal
		"+inf",       // double pseudo-literal
		"2147483647", // INT_MAX
		"2147483648"  // Overflow (should be impossible for int)
	};

	for (int i = 0; i < 9; ++i)
	{
		std::cout << "\nTest " << i + 1 << ": [./convert " << tests[i]
				  << "]" << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		ScalarConverter::convert(tests[i]);
	}

	return 0;
}
