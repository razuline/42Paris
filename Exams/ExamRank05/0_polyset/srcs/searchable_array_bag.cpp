/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 20:39:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

searchable_array_bag::searchable_array_bag() :
	array_bag()
{
	// std::cout << "Default constructor called" << std::endl;
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &copy) :
	array_bag(copy)
{
	// std::cout << "Copy constructor called" << std::endl;
}

searchable_array_bag
&searchable_array_bag::operator=(const searchable_array_bag &other)
{
	if (this != &other)
	{
		array_bag::operator=(other);
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

searchable_array_bag::~searchable_array_bag()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

bool
searchable_array_bag::has(int value) const
{
	// Loop through the data to find a match
	for (int i = 0; i < this->size; ++i)
	{
		if (this->data[i] == value)
			return true;
	}
	return false;
}
