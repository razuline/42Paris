/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:25:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:30:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	const int	size = 4;
	Animal		*animals[size];

	std::cout << "--- 1. CREATING ANIMALS ---" << std::endl;
	for (int i = 0; i < size; i++)
	{
		if (i < size / 2)
			animals[i] = new Dog(); // First half are Dogs
		else
			animals[i] = new Cat(); // Second half are Cats
	}

	std::cout << "\n--- 2. TESTING DEEP COPY ---" << std::endl;
	// This scope {} forces 'tmp' to be destroyed before the program ends
	{
		Dog	basic;
		basic.getBrain()->setIdea(0, "I want bone"); // Set an idea

		Dog	tmp = basic; // Calls Copy Constructor
		// If this was Shallow Copy, 'tmp' would point to 'basic's brain.
		
		// Accessing tmp's brain works fine
		std::cout << "Basic idea: " << basic.getBrain()->getIdea(0) << std::endl;
		std::cout << "Tmp idea:   " << tmp.getBrain()->getIdea(0) << std::endl;
	} // 'tmp' is destroyed here. 
	  // If Shallow Copy: tmp deletes the brain. 'basic' now has a pointer 
	  	//to freed memory.
	  // If Deep Copy: tmp deletes its OWN brain. 'basic' is safe.
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
