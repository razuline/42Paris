/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:39:58 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/20 20:24:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int ac, char **av)
{
	// Check for at least one argument
	if (ac < 2)
	{
		std::cerr << "Error: No sequence provided." << std::endl;
		std::cout << "Usage: ./PmergeMe [positive_int1] [positive_int2] ..."
				  << std::endl;
		return 1;
	}

	try
	{
		PmergeMe	sorter;

		// Display original sequence
		sorter.printBefore(ac, av);

		// Run the Ford-Johnson algorithm for both containers
		// This includes parsing time as per subject requirements
		sorter.run(ac, av);

		// Display sorted sequence
		sorter.printAfter();

		// Display timing results for comparison
		sorter.printTime();
	}
	catch (const std::exception &e)
	{
		// Handle invalid inputs (negative numbers, non-digits, etc.)
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
