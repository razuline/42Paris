/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_bag.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:31:16 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 15:20:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** EXAM ASSIGNMENTS **************************** */
/* ************************************************************************** */

#include "array_bag.hpp"
#include <iostream>

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

array_bag::array_bag() :
	data(0),
	size(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

array_bag::array_bag(const array_bag &copy)
{
	size = copy.size;
	data = new int[size];

	for (int i = 0; i < size; i++)
		data[i] = copy.data[i];

	// std::cout << "Copy constructor called" << std::endl;
}

array_bag
&array_bag::operator=(const array_bag &other)
{
	this->clear();
	if (other.size > 0)
	{
		this->data = new int[other.size];

		for (int i = 0; i < other.size; i++)
			this->data[i] = other.data[i];
	}
	else
		this->data = 0; // Use 0
	this->size = other.size;

	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

array_bag::~array_bag()
{
	if (data != 0)
	{
		delete[] data;
		data = 0;
	}

	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

void
array_bag::insert(int item)
{
	int	*new_data = new int[size + 1];

	for (int i = 0; i < size; i++)
		new_data[i] = data[i];

	new_data[size] = item;

	if (data != 0)
		delete[] data;

	data = new_data;
	size++;
}

void
array_bag::insert(int *items, int count)
{
	int	*new_data = new int[size + count];

	for (int i = 0; i < size; i++)
		new_data[i] = data[i];

	for (int i = 0; i < count; i++)
		new_data[size + i] = items[i];

	if (data != 0)
		delete[] data;

	data = new_data;
	size += count;
}

void
array_bag::print() const
{
	for (int i = 0; i < this->size; i++)
		std::cout << data[i] << " ";

	std::cout << std::endl;
}

void
array_bag::clear()
{
	if (this->data != 0) // Comparison with 0
	{
		delete [] this->data;
		this->data = 0;
	}
	this->size = 0;
}
