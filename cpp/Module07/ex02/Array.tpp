/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:43:27 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/19 17:43:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
# define ARRAY_TPP

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

/* --- Default Constructor --- */
// Creates an empty array with no elements
template <typename T>
Array<T>::Array() :
	_arr(NULL),
	_arrSize(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

/* --- Parameterised Constructor --- */
// Creates an array of n elements initialised by default.
// Uses new[] for allocation as required.
template <typename T>
Array<T>::Array(unsigned int n) :
	_arrSize(n)
{
	this->_arr = new T[n](); // The empty () ensure value-init (e.g. 0 for ints)

	// std::cout << "Parameterised constructor called" << std::endl;
}

/* --- Copy Constructor --- */
// Performs a deep copy so that the new array is independent of the original
template <typename T>
Array<T>::Array(const Array &copy) :
	_arrSize(copy._arrSize)
{
	// 1. Allocate new memory for the copy
	this->_arr = new T[this->_arrSize]();

	// 2. Copy each element individually to ensure deep copy
	for (unsigned int i = 0; i < this->_arrSize; i++)
	{
		this->_arr[i] = copy._arr[i];
	}
	// std::cout << "Copy constructor called" << std::endl;
}

/* --- Copy Assignment Operator --- */
// Safely replaces current data with a deep copy of another array
template <typename T>
Array<T>
&Array<T>::operator=(const Array &other)
{
	// 1. Check for self-assignment (e.g., a = a)
	if (this != &other)
	{
		// 2. Free existing memory to prevent leaks
		delete[] this->_arr;

		// 3. Copy size and allocate new memory
		this->_arrSize = other._arrSize;
		this->_arr = new T[this->_arrSize]();

		// 4. Perform deep copy of elements
		for (unsigned int i = 0; i < this->_arrSize; i++)
		{
			this->_arr[i] = other._arr[i];
		}
	}
	// 5. Return reference to this object for chained assignments
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

/* --- Destructor --- */
// Frees the dynamically allocated memory to prevent memory leaks
template <typename T>
Array<T>::~Array()
{
	if (this->_arr != NULL)
		delete[] this->_arr; // delete[] for memory allocated with new[]

	// std::cout << "Destructor called" << std::endl;
}

/* --------------------------------- METHODS -------------------------------- */

// Returns the number of elements in the array.
// This member function doesn't modify the instance.
template <typename T>
unsigned int
Array<T>::size() const
{
	return this->_arrSize;
}

// Subscript operator for accessing elements.
// Throws std::exception if the index is out of bounds.
template <typename T>
T
&Array<T>::operator[](unsigned int idx)
{
	// Check if the index is out of bounds
	if (idx >= this->_arrSize)
	{
		throw OutOfBoundsException(); // Prevents accessing non-allocated memory
	}
	return this->_arr[idx];
}

// Subscript operator for accessing elements in a const-safe way.
// Throws std::exception if the index is out of bounds.
template <typename T>
const T
&Array<T>::operator[](unsigned int idx) const
{
	if (idx >= this->_arrSize)
	{
		throw OutOfBoundsException();
	}
	// Return the element as a const reference
	return this->_arr[idx];
}

#endif