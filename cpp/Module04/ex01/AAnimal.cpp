/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:12:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 13:33:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

AAnimal::AAnimal(void)
{
	std::cout << "AAnimal constructor called..." << std::endl;
}

AAnimal::AAnimal(const AAnimal &copy) : _type(copy._type)
{
	std::cout << "AAnimal copy constructor called..." << std::endl;
}

AAnimal
&AAnimal::operator=(const AAnimal &other)
{
	if (this != &other)
		this->_type = other._type;
	std::cout << "AAnimal assignment operator called..." << std::endl;
	return *this;
}

AAnimal::~AAnimal(void)
{
	std::cout << "AAnimal destructor called..." << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string
AAnimal::getType(void) const
{
	return _type;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
AAnimal::makeSound(void) const
{
	std::cout << "The animals make sounds:" << std::endl;
}
