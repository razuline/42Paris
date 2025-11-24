/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:54:59 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 19:35:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

// Default Constructor
Cat::Cat(void) : Animal()
{
	this->_type = "Cat";
	this->_brain = new Brain(); // Allocate a NEW Brain for this specific Cat
	std::cout << "Cat constructor called..." << std::endl;
}

// Copy Constructor (Deep Copy)
Cat::Cat(const Cat &copy) : Animal(copy)
{
	std::cout << "Cat copy constructor called..." << std::endl;
	// Instead of pointing to src._brain (Shallow Copy),
		// we create a NEW Brain and initialise it with src._brain.
	this->_brain = new Brain(*copy._brain);
}

// Assignment Operator (Deep Copy)
Cat
&Cat::operator=(const Cat &other)
{
	std::cout << "Cat assignment operator called..." << std::endl;
	if (this != &other)
	{
		// 1. Copy the base class parts (type)
		Animal::operator=(other);
		// 2. Delete the OLD brain to prevent memory leak
		delete this->_brain;
		// 3. Allocate a NEW brain and copy data from source
		this->_brain = new Brain(*other._brain);
	}
	return *this;
}

// Destructor
Cat::~Cat(void)
{
	std::cout << "Cat destructor called..." << std::endl;
	// We must manually delete the Brain we allocated, otherwise -> Leak.
	delete this->_brain;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Cat::makeSound(void) const
{
	std::cout << "Cat: Meow!" << std::endl;
}
