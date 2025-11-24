/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:12:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:42:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A_Animal.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

A_Animal::A_Animal(void)
{
	std::cout << "A_Animal constructor called..." << std::endl;
}

A_Animal::A_Animal(const A_Animal &copy) : _type(copy._type)
{
	std::cout << "A_Animal copy constructor called..." << std::endl;
}

A_Animal
&A_Animal::operator=(const A_Animal &other)
{
	if (this != &other)
		this->_type = other._type;
	std::cout << "A_Animal assignment operator called..." << std::endl;
	return *this;
}

A_Animal::~A_Animal(void)
{
	std::cout << "A_Animal destructor called..." << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string
A_Animal::getType(void) const
{
	return _type;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
A_Animal::makeSound(void) const
{
	std::cout << "The animals make sounds:" << std::endl;
}
