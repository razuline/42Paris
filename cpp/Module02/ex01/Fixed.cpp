/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:09:35 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/08 15:47:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
	std::cout << "Default constructor called" << std::endl;
	this->_fixed = 0;
}

Fixed::Fixed(const int n)
{
	std::cout << "Int constructor called" << std::endl;
	this->_fixed = n << _bits;
}

Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	this->_fixed = roundf(f * 256);
}

Fixed::Fixed(const Fixed &copy)
{
	std::cout << "Copy constructor called" << std::endl;
	this->_fixed = copy._fixed;
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

Fixed
&Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called" << std::endl;

	if (this != &other)
	{
		this->_fixed = other.getRawBits();
	}
	return *this;
}

void
Fixed::setRawBits(int const raw)
{
	this->_fixed = raw;
}

int
Fixed::getRawBits(void) const
{
	return this->_fixed;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

int
Fixed::toInt(void) const
{
	return this->_fixed >> _bits;
}

float
Fixed::toFloat(void) const
{
	return this->_fixed / 256.0f;
}

std::ostream
&operator<<(std::ostream &out, const Fixed &value)
{
	// Demander à l'objet 'value' de se convertir en float,
	// puis insèrer ce float dans le flux de sortie 'out'.
	out << value.toFloat();
	return out;
}
