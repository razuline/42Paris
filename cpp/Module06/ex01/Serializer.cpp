/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:36:19 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:57:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Serializer::Serializer()
{
	//std::cout << "Default constructor called" << std::endl;
}

Serializer::Serializer(const Serializer &src)
{
	(void)src;

	//std::cout << "Copy constructor called" << std::endl;
}

Serializer
&Serializer::operator=(const Serializer &rhs)
{
	(void)rhs;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

Serializer::~Serializer()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- STATIC METHODS ----------------------------- */

// serialize: converts Data* to uintptr_t.
// reinterpret_cast is used here to treat the pointer's memory address
// as a raw integer value without changing the underlying bits.
uintptr_t
Serializer::serialize(Data *ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

// deserialize: converts uintptr_t back to Data*.
// This reconstructs the pointer from the integer value, allowing us
// to access the original memory location and its data.
Data
*Serializer::deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}
