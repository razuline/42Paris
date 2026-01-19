/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:14:42 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/19 17:37:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <exception>
# include <iostream>

/* ---------------------------------- CLASS --------------------------------- */

// Class template for a dynamic array with bounds checking
template <typename T>
class Array
{
private:
	T				*_arr;    // Pointer to the dynamically allocated array
	unsigned int	_arrSize; // Number of elements in the array

public:
	/* --- Orthodox Canonical Form --- */
	Array();
	Array(unsigned int n);
	Array(const Array &copy);
	Array	&operator=(const Array &other);
	~Array();

	/* --- Mandatory Methods --- */
	unsigned int	size() const;
	T				&operator[](unsigned int idx); // For change elements
	const T			&operator[](unsigned int idx) const; // For const arrays

	/* --- Custom Exception Class --- */
	// For out of bounds access
	class OutOfBoundsException : public std::exception
	{
	public:
		virtual const char	*what() const throw()
		{
			return "Error: Index is out of bounds!";
		}
	};
};

# include "Array.tpp"

#endif