/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:43:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:50:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

WrongCat::WrongCat(void)
{
	std::cout << "WrongCat is here!" << std::endl;
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat run out!" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
WrongCat::makeSound(void) const
{
	std::cout << "Meow??? (but wrongly)" << std::endl;
}
