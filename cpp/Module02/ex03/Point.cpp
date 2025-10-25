/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:30:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/25 16:13:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

/* ------------------------ CONSTRUCTOR & DESTRUCTOR ------------------------ */

Point::Point(void) : _x(0), _y(0)
{
	//std::cout << "[ POINT ] Default constructor called" << std::endl;
}

Point::Point(const float x_val, const float y_val) : _x(x_val), _y(y_val)
{
	//std::cout << "[ POINT ] Float constructor called" << std::endl;
}

Point::Point(const Point &copy) : _x(copy._x), _y(copy._y)
{
	//std::cout << "[ POINT ] Copy constructor called" << std::endl;
}

Point::~Point(void)
{
	//std::cout << "[ POINT ] Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

Point
&Point::operator=(const Point &other)
{
	//std::cout << "[ POINT ] Copy assignment operator called" << std::endl;

	// On ne peut rien assigner car les membres _x et _y sont const.
	// Cette fonction existe uniquement pour respecter la forme canonique.

	// La ligne suivante est une astuce pour dire au compilateur :
	// "Je sais que je n'utilise pas le paramètre 'other', et c'est volontaire".
	// Cela évite d'avoir un avertissement (warning) à la compilation.
	(void)other;

	return *this;
}

Fixed
Point::getX(void) const
{
	return this->_x;
}

Fixed
Point::getY(void) const
{
	return this->_y;
}
