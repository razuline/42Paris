/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:25:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:52:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "A_Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	// Array of pointers to abstract base class (polymorphism!)
	const int	size = 4;
	A_Animal	*animals[size];

	std::cout << "--- 1. CREATING ANIMALS ---" << std::endl;
	for (int i = 0; i < size; i++)
	{
		// Fill the first half with Dogs, the second half with Cats
		if (i < size / 2)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}

	std::cout << "\n--- 2. TESTING DEEP COPY ---" << std::endl;
	// Test deep copy for correct memory management (no shared Brain!)
	{
		Dog	basic; // Construct a Dog
		basic.getBrain()->setIdea(0, "I want bone"); // Set a brain idea

		Dog	tmp = basic; // Copy construct Dog (should deep copy brain)
		
		// Both dogs have independent Brain objects
		std::cout << "Basic idea: " << basic.getBrain()->getIdea(0) << std::endl;
		std::cout << "Tmp idea:   " << tmp.getBrain()->getIdea(0) << std::endl;
	}
	// tmp goes out of scope and is destroyed,
		// but basic's Brain is unaffected if deep copy is correct.
	std::cout << "Basic was not affected by tmp destruction!" << std::endl;

	std::cout << "\n--- 3. DELETING ANIMALS ---" << std::endl;
	for (int i = 0; i < size; i++)
	{
		// This calls ~Animal(). Because it's virtual,
			//it calls ~Dog() / ~Cat() first.
		// Then ~Dog() / ~Cat() calls delete _brain.
		delete animals[i];
	}

	return 0;
}
