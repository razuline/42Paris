/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:44:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 14:46:02 by erazumov         ###   ########.fr       */
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

vect2::vect2(int x, int y) : _x(x), _y(y) {}

vect2::vect2(const vect2 &copy) : _x(copy._x), _y(copy._y) {}

vect2 &vect2::operator=(const vect2 &other) {
	if (this != &other) {
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

vect2::~vect2() {}

/* --- Arithmetic --- */

vect2 vect2::operator+(const vect2 &other) const {
	return vect2(_x + other._x, _y + other._y);
}

vect2 &vect2::operator+=(const vect2 &other) {
	_x += other._x;
	_y += other._y;
	return *this;
}

vect2 vect2::operator-(const vect2 &other) const {
	return vect2(_x - other._x, _y - other._y);
}

vect2 &vect2::operator-=(const vect2 &other) {
	_x -= other._x;
	_y -= other._y;
	return *this;
}

vect2 vect2::operator-() const {
	return vect2(-_x, -_y);
}

/* --- Scalar Multiplication --- */

vect2 vect2::operator*(int scalar) const {
	return vect2(_x * scalar, _y * scalar);
}

vect2 &vect2::operator*=(int scalar) {
	_x *= scalar;
	_y *= scalar;
	return *this;
}

vect2 operator*(int scalar, const vect2 &v) {
	return v * scalar; // Reuses the operator*(int) logic
}

/* --- Increment / Decrement --- */

vect2 &vect2::operator++() {
	_x++; _y++;
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2 &vect2::operator--() {
	_x--; _y--;
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 temp(*this);
	--(*this);
	return temp;
}

/* --- Access & Comparison --- */

int &vect2::operator[](int i) {
	return (i == 0) ? _x : _y;
}

const int &vect2::operator[](int i) const {
	return (i == 0) ? _x : _y;
}

bool vect2::operator==(const vect2 &other) const {
	return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2 &other) const {
	return !(*this == other);
}

/* --- Output --- */

std::ostream &operator<<(std::ostream &os, const vect2 &v) {
	os << "{" << v._x << ", " << v._y << "}";
	return os;
}
