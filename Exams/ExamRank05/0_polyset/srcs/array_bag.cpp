/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_bag.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:31:16 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 21:17:33 by erazumov         ###   ########.fr       */
/*                                                                            */
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
	this->data = new int[copy.size];

	for (int i = 0; i < copy.size; i++)
		this->data[i] = copy.data[i];

	this->size = copy.size;

	// std::cout << "Copy constructor called" << std::endl;
}

array_bag
&array_bag::operator=(const array_bag &other)
{
	this->clear();
	this->data = new int[other.size];

	for (int i = 0; i < other.size; i++)
		this->data[i] = other.data[i];

	this->size = other.size;

	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

array_bag::~array_bag()
{
	delete [] this->data;

	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

void
array_bag::insert(int val)
{
	int	*tmp = new int[size + 1];

	for (int i = 0; i < size; i++)
		tmp[i] = this->data[i];

	tmp[this->size] = val;
	delete [] this->data;

	this->data = tmp;
	this->size++;
}

void
array_bag::insert(int *a, int s)
{
	for (int i = 0; i < s; i++)
		this->insert(a[i]);
}

void
array_bag::print() const
{
	for (int i = 0; i < this->size; i++)
		std::cout << this->data[i] << " ";

	std::cout << std::endl;
}

void
array_bag::clear()
{
	delete [] this->data;

	this->data = 0;
	this->size = 0;
}
