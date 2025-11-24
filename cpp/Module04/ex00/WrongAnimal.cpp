/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:38:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:53:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

WrongAnimal::WrongAnimal(void)
{
	std::cout << "WrongAnimal is here!" << std::endl;
}

WrongAnimal::~WrongAnimal(void)
{
	std::cout << "WrongAnimal run out!" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string
WrongAnimal::getType(void) const
{
	return _type;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
WrongAnimal::makeSound(void) const
{
	std::cout << "Some generic WrongAnimal sound" << std::endl;
}
