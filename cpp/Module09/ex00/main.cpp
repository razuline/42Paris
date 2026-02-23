/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 23:23:31 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/21 19:56:04 by erazumov         ###   ########.fr       */
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

	// 2. Load the data.csv AND STOP if it fails
	if (btc.loadDatabase("data.csv") == false)
	{
		std::cerr << "Error: database file missing." << std::endl;
		return 1;
	}

	// 3. Process the input ONLY if database is loaded
	btc.processInput(av[1]);

	return 0;
}
