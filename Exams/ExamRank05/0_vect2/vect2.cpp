/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:44:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 18:25:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect2.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

vect2::vect2() :
	_x(0),
	_y(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

vect2::vect2(int x, int y) :
	_x(x),
	_y(y)
{
	// std::cout << "Default constructor called" << std::endl;
}

vect2::vect2(const vect2 &copy) :
	_x(copy._x),
	_y(copy._y)
{
	// std::cout << "Copy constructor called" << std::endl;
}

vect2
&vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

vect2::~vect2()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

/* --- Arithmetic --- */

vect2
vect2::operator+(const vect2 &other) const
{
	return vect2(_x + other._x, _y + other._y);
}

// Returns *this to allow chained assignments like v1 += v2 += v3
vect2
&vect2::operator+=(const vect2 &other)
{
	_x += other._x;
	_y += other._y;

	return *this;
}

vect2
vect2::operator-(const vect2 &other) const
{
	return vect2(_x - other._x, _y - other._y);
}

vect2
&vect2::operator-=(const vect2 &other)
{
	_x -= other._x;
	_y -= other._y;

	return *this;
}

// Negates the vector: {1, 2} becomes {-1, -2}
vect2
vect2::operator-() const
{
	return vect2(-_x, -_y);
}

/* --- Scalar Multiplication --- */

vect2
vect2::operator*(int scalar) const
{
	return vect2(_x * scalar, _y * scalar);
}

vect2 &vect2::operator*=(int scalar)
{
	_x *= scalar;
	_y *= scalar;

	return *this;
}

/* --- Increment / Decrement --- */

// Prefix: increments and returns the updated object
vect2
&vect2::operator++()
{
	_x++;
	_y++;

	return *this;
}

// Postfix: saves a copy (tmp), increments, then returns the old copy
vect2
vect2::operator++(int)
{
	vect2	tmp(*this);

	++(*this);

	return tmp;
}

vect2
&vect2::operator--()
{
	_x--;
	_y--;

	return *this;
}

vect2
vect2::operator--(int)
{
	vect2	tmp(*this);

	--(*this);

	return tmp;
}

/* --- Access & Comparison --- */

// Returns a reference to allow modification: v[0] = 10;
int
&vect2::operator[](int i)
{
	return (i == 0) ? _x : _y;
}

// Required for const objects (read-only access)
const int
&vect2::operator[](int i) const
{
	return (i == 0) ? _x : _y;
}

bool
vect2::operator==(const vect2 &other) const
{
	return (_x == other._x && _y == other._y);
}

bool
vect2::operator!=(const vect2 &other) const
{
	return !(*this == other);
}

/* --------------------- EXTERNAL FUNCTIONS (NON-MEMBER) -------------------- */

/**
 * Handles scalar multiplication from the left: 3 * v
 * Simply calls the member operator: v * 3
 */
vect2
operator*(int scalar, const vect2 &v)
{
	return v * scalar;
}

/**
 * Handles printing: std::cout << v
 */
std::ostream
&operator<<(std::ostream &os, const vect2 &v)
{
	os << "{" << v[0] << ", " << v[1] << "}";

	return os;
}
