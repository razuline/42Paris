/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:34:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:03:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_HPP
# define VECT2_HPP

# include <iostream>

class vect2
{
private:
	int	_x;
	int	_y;

public:
	/* --- Orthodox Canonical Form --- */
	vect2();                                 // For: vect2 v1;
	vect2(int x, int y);                     // For: vect2 v2(1, 2);
	vect2(const vect2 &copy);                // For: vect2 v3(v2);
	vect2	&operator=(const vect2 &other);  // For: v4 = v2;
	~vect2();

	/* --- Arithmetic Operators --- */
	vect2	operator+(const vect2 &other) const;
	vect2	&operator+=(const vect2 &other); // Returns ref for: v2 += v2 += v3
	vect2	operator-(const vect2 &other) const;
	vect2	&operator-=(const vect2 &other);
	vect2	operator-() const;               // For: -v2. Unary minus

	/* --- Scalar Multiplication --- */
	vect2	operator*(int scalar) const;     // For: v3 * 2
	vect2	&operator*=(int scalar);

	/* --- Increment / Decrement --- */
	vect2	&operator++();    // Prefix ++v
	vect2	operator++(int);  // Postfix v++
	vect2	&operator--();    // Prefix --v
	vect2	operator--(int);  // Postfix v--

	/* --- Access & Comparison --- */
	int			&operator[](int i);           // For v1[1] = 12
	const int	&operator[](int i) const;     // For const v3[1]
	bool		operator==(const vect2 &other) const;
	bool		operator!=(const vect2 &other) const;
};

// Global operators for scalar * vect and printing
vect2
operator*(int scalar, const vect2 &v);

std::ostream
&operator<<(std::ostream &os, const vect2 &obj);

#endif