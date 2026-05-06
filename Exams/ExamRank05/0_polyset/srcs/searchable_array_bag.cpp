/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:39:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_array_bag.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

searchable_array_bag::searchable_array_bag() :
	array_bag()
{
}

searchable_array_bag::searchable_array_bag(const searchable_array_bag &copy) :
	array_bag(copy)
{
}

searchable_array_bag
&searchable_array_bag::operator=(const searchable_array_bag &other)
{
	if (this != &other)
		array_bag::operator=(other);
	return *this;
}

searchable_array_bag::~searchable_array_bag()
{
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

bool
searchable_array_bag::has(int value) const
{
	// Linear search: check every element one by one
	for (int i = 0; i < this->size; ++i)
	{
		if (this->data[i] == value)
			return true;
	}
	return false;
}
