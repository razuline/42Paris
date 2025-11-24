/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:28:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:44:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Dog::Dog(void) : A_Animal()
{
	this->_type = "Dog";
	this->_brain = new Brain();
	std::cout << "Dog constructor called..." << std::endl;
}

Dog::Dog(const Dog &copy) : A_Animal(copy)
{
	std::cout << "Dog copy constructor called..." << std::endl;
	this->_brain = new Brain(*copy._brain);
}

Dog
&Dog::operator=(const Dog &other)
{
	std::cout << "Dog assignment operator called..." << std::endl;
	if (this != &other)
	{
		A_Animal::operator=(other);
		delete this->_brain;
		this->_brain = new Brain(*other._brain);
	}
	return *this;
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor called..." << std::endl;
	delete this->_brain;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Dog::makeSound(void) const
{
	std::cout << "Dog: Woof!" << std::endl;
}
