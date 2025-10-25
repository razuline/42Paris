/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:19:06 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/25 16:10:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include <cmath>
# include <iostream>
# include <string>
# include "Fixed.hpp"

class Point
{
private:
	const Fixed	_x;
	const Fixed	_y;

public:
	Point(void);                                 // Constructeur par défaut
	Point(const float x_val, const float y_val); // Constructeur par paramètres
	Point(const Point &copy);                    // Constructeur de copie
	~Point(void);                                // Destructeur

	Point	&operator=(const Point &other);      // Opérateur d'affectation

	Fixed	getX(void) const;                      // Getter pour x
	Fixed	getY(void) const;                      // Getter pour y
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif