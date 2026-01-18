/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:10:32 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 18:00:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// Randomly instantiates A, B, or C and returns it as a Base pointer.
Base	*generate()
{
	// Generate a random number between 0 and 2
	int	r = std::rand() % 3;

	if (r == 0)
		return new A();
	if (r == 1)
		return new B();
	return new C();
}

// Identifies the type using pointers.
// dynamic_cast returns NULL if the cast fails.
void	identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown type" << std::endl;
}

// Identifies the type using references.
// Using a ptr inside this function is forbidden => try-catch blocks.
// dynamic_cast throws an exception if a reference cast fails.
void	identify(Base &p)
{
	// Try to cast to A
	try
	{
		A	&a = dynamic_cast<A &>(p);
		(void)a; // Cast successful
		std::cout << "A" << std::endl;
		return; // Found the type, exit function
	}
	catch(const std::exception &e) // Catch and move to the next check
	{
		// Try to cast to B
		try
		{
			B	&b = dynamic_cast<B &>(p);
			(void)b;
			std::cout << "B" << std::endl;
			return;
		}
		catch(const std::exception &e)
		{
			// Try to cast to C
			try
			{
				C	&c = dynamic_cast<C &>(p);
				(void)c;
				std::cout << "C" << std::endl;
				return;
			}
			catch(const std::exception &e)
			{
				std::cout << "Unknown type" << std::endl;
			}
		}
	}
}

int	main(void)
{
	// Seed the random generator with the current time
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "--- Starting Identification Tests ---" << std::endl;

	for (int i = 0; i < 5; ++i)
	{
		std::cout << "\nTest #" << i + 1 << ":" << std::endl;

		// Generate a random object
		Base	*instance = generate();

		// Test pointer-based identification
		std::cout << "Identify (Pointer):   ";
		identify(instance);

		// Test reference-based identification
		std::cout << "Identify (Reference): ";
		identify(*instance);

		// Free allocated memory to avoid leaks
		delete instance;
		std::cout << "-------------------------------------" << std::endl;
	}
	return 0;
}
