/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:31:19 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 12:53:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>

int	main(void)
{
	// Test 1: Vectors
	std::cout << "--- Test Vector ---" << std::endl;

	std::vector<int>	v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);

	try
	{
		std::vector<int>::iterator	it = easyfind(v, 20);
		std::cout << "Found: " << *it << std::endl;

		// Try to find a number that isn't present
		easyfind(v, 42);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Test 2: List
	std::cout << "\n--- Test List ---" << std::endl;

	std::list<int>	l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);

	try
	{
		std::list<int>::iterator	it = easyfind(l, 3);
		std::cout << "Found: " << *it << std::endl;

		easyfind(l, -5);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
