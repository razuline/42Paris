/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:24 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/10 18:56:45 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"
#include <iostream>

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

set::set(searchable_bag &bag) :
	_bag(&bag)
{
}

set::set(const set &copy) :
	_bag(copy._bag)
{
}

set
&set::operator=(const set &other)
{
	if (this != &other)
		_bag = other._bag;
	return *this;
}

set::~set()
{
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

/* --- Logic: Preventing Duplicates --- */
void
set::insert(int value)
{
	// Check if the bag already contains the value before inserting
	if (this->_bag != NULL &&
		this->_bag->has(value) == false)
	{
		this->_bag->insert(value);
	}
}

// Insert an array of values
void
set::insert(int *array, int size)
{
	if (this->_bag != NULL &&
		array != NULL)
	{
		for (int i = 0; i < size; i++)
			this->insert(array[i]); // Reuses the single insert logic
	}
}

/* --- Delegation Methods --- */

bool
set::has(int value) const
{
	return _bag ? _bag->has(value) : false;
}

void
set::print() const
{
	if (_bag)
		_bag->print();
}

void
set::clear()
{
	if (_bag)
		_bag->clear();
}

/* --------------------------------- GETTER --------------------------------- */

searchable_bag
&set::get_bag() const
{
	return *_bag;
}
