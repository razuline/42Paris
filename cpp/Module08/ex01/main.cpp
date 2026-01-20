/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 18:25:39 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 18:32:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <vector>
#include <ctime>   // std::time
#include <cstdlib> // std::rand

int	main(void)
{
	// --- Test 1: Subject basic test ---
	std::cout << "--- Subject Test ---" << std::endl;
	try
	{
		Span	sp = Span(5); // Create Span with capacity 5

		sp.addNumber(6);      // Adding numbers one by one
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		// Should output 2 and 14
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest:  " << sp.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// --- Test 2: Large numbers test (10,000+) ---
	std::cout << "\n--- Large Dataset Test (10,000 numbers) ---" << std::endl;
	try
	{
		unsigned int	n = 10000;
		Span			bigSpan(n);

		std::vector<int>	randomNums;
		std::srand(std::time(0));

		for (unsigned int i = 0; i < n; ++i)
			randomNums.push_back(std::rand());

		// Fill Span efficiently using a range of iterators
		bigSpan.addNumbers(randomNums.begin(), randomNums.end());

		std::cout << "Shortest: " << bigSpan.shortestSpan() << std::endl;
		std::cout << "Longest:  " << bigSpan.longestSpan() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// --- Test 3: Exception handling ---
	std::cout << "\n--- Exception Test ---" << std::endl;
	try
	{
		Span	small(1);

		small.addNumber(42);
		small.shortestSpan(); // This should throw
	}
	catch (const std::exception &e)
	{
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	return 0;
}
