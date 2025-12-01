/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:08:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 14:13:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

// Default Constructor
Cure::Cure() : AMateria("cure")
{
	// std::cout << "Cure constructor called..." << std::endl;
}

// Copy Constructor (Deep Copy)
Cure::Cure(const Cure &copy) : AMateria(copy)
{
	// std::cout << "Cure copy constructor called..." << std::endl;
}

// Assignment Operator (Deep Copy)
Cure
&Cure::operator=(const Cure &other)
{
	// std::cout << "Cure assignment operator called..." << std::endl;
	if (this != &other)
		AMateria::operator=(other);
	return *this;
}

// Destructor
Cure::~Cure(void)
{
	// std::cout << "Cure destructor called..." << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

AMateria
*Cure::clone() const
{
	return new Cure(*this);
}

void
Cure::use(ICharacter& target)
{
	std::cout << "* heals <name>’s wounds " << target.getName() << " *"
			<< std::endl;
}