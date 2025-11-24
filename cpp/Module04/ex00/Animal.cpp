/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:12:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:40:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Animal::Animal(void)
{
	//std::cout << "This is an animal!" << std::endl;
}

Animal
&Animal::operator=(const Animal &other)
{
	if (this != &other)
		this->_type = other._type;
	return *this;
	std::cout << "Animal assignment operator called" << std::endl;
}

Animal::~Animal(void)
{
	//std::cout << "Animal " << this->_type << "was deleted!" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string
Animal::getType(void) const
{
	return _type;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Animal::makeSound(void) const
{
	std::cout << "The animals make sounds:" << std::endl;
}
