/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:31 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 17:24:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>

int	main(int ac, char **av)
{
	// 1. Check if the user provided exactly one argument
	if (ac != 2)
	{
		// Message requis
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}

	BitcoinExchange	btc;

	// 2. Load the database and check for success in one go
	if (!btc.loadDatabase("data.csv"))
	{
		return 1;
	}

	// 3. Process the input file provided by the user
	btc.processInput(av[1]);

	return 0;
}
