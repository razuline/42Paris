/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 22:23:43 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/27 22:55:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int	main(void)
{
	// Initialise the MutantStack
	MutantStack<int>	mstack;

	// Push elements onto the stack
	mstack.push(5);
	mstack.push(17);

	// Displaying the top element
	std::cout << "Top: " << mstack.top() << std::endl; // Should be 17
	mstack.pop(); // Removing the top element
	std::cout << "Size: " << mstack.size() << std::endl; // Should be 1

	// Add more elements
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	// Standard Forward Iteration
	MutantStack<int>::iterator	it = mstack.begin();
	MutantStack<int>::iterator	ite = mstack.end();

	std::cout << "Stack (forward): ";
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	// Reverse Iteration
	// This demonstrates the 'mutant' ability to traverse backwards
	MutantStack<int>::reverse_iterator	rit = mstack.rbegin();
	MutantStack<int>::reverse_iterator	rite = mstack.rend();

	std::cout << "Stack (reverse): ";
	while (rit != rite)
	{
		std::cout << *rit << " ";
		++rit;
	}
	std::cout << std::endl;

	// Compatibility check: copying into a standard stack
	std::stack<int> s(mstack);
	return 0;
}
