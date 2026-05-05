/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:24 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 21:10:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"
#include <iostream>

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

set::set(searchable_bag &bag) :
	_bag(&bag)
{
	// std::cout << "Default constructor called" << std::endl;
}

set::set(const set &copy) :
	_bag(copy._bag)
{
	// std::cout << "Copy constructor called" << std::endl;
}

set
&set::operator=(const set &other)
{
	if (this != &other)
		_bag = other._bag;
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

set::~set()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

// Insert a single value (no duplicates!)
void
set::insert(int value)
{
	if (this->_bag != NULL && this->_bag->has(value) == false)
	{
		this->_bag->insert(value);
	}
}

// Insert an array of values
void
set::insert(int *array, int size)
{
	if (this->_bag != NULL && array != NULL)
	{
		for (int i = 0; i < size; i++)
		{
			this->insert(array[i]); // Re-use the single insert logic
		}
	}
}

bool
set::has(int value) const
{
	if (this->_bag == NULL)
		return false;
	return this->_bag->has(value);
}

void
set::print() const
{
	if (this->_bag != NULL)
	{
		this->_bag->print();
	}
}

void
set::clear()
{
	if (this->_bag != NULL)
	{
		this->_bag->clear();
	}
}

/* --------------------------------- GETTER --------------------------------- */

searchable_bag
&set::get_bag() const
{
	return *(this->_bag);
}
