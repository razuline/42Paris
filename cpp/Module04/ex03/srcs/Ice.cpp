/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:42:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 14:07:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

// Default Constructor
Ice::Ice() : AMateria("ice")
{
	// std::cout << "Ice constructor called..." << std::endl;
}

// Copy Constructor (Deep Copy)
Ice::Ice(const Ice &copy) : AMateria(copy)
{
	// std::cout << "Ice copy constructor called..." << std::endl;
}

// Assignment Operator (Deep Copy)
Ice
&Ice::operator=(const Ice &other)
{
	// std::cout << "Ice assignment operator called..." << std::endl;
	if (this != &other)
		AMateria::operator=(other);
	return *this;
}

// Destructor
Ice::~Ice(void)
{
	// std::cout << "Ice destructor called..." << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

AMateria
*Ice::clone() const
{
	return new Ice(*this);
}

void
Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *"
			<< std::endl;
}
