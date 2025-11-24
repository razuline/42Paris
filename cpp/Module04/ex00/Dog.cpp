/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:28:32 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:23:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Dog::Dog(void)
{
	std::cout << "Dog is here!" << std::endl;
}

Dog
&Dog::operator=(const Dog &other)
{
	if (this != &other)
		Animal::operator=(other);
	return *this;
	std::cout << "Dog assignment operator called." << std::endl;
}

Dog::~Dog(void)
{
	std::cout << "Dog " << this->_type << "run out!" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Dog::makeSound(void) const
{
	std::cout << "The dog says : woof woof" << std::endl;
}
