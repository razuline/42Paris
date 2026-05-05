/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:34:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 16:45:19 by erazumov         ###   ########.fr       */
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
	vect2();
	vect2(unsigned long long n);
	vect2(const vect2 &copy);
	vect2	&operator=(const vect2 &other);
	~vect2();

	/* --- Orthodox Canonical Form --- */
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &copy);
	vect2	&operator=(const vect2 &other);
	~vect2();

	/* --- Arithmetic Operators --- */
	vect2	operator+(const vect2 &other) const;
	vect2	&operator+=(const vect2 &other);
	vect2	operator-(const vect2 &other) const;
	vect2	&operator-=(const vect2 &other);
	vect2	operator-() const; // Unary minus: -v2

	/* --- Scalar Multiplication --- */
	vect2	operator*(int scalar) const;
	vect2	&operator*=(int scalar);
	// Friend function to allow: scalar * vect2 (e.g., 3 * v2)
	friend vect2 operator*(int scalar, const vect2 &v);

	/* --- Increment / Decrement --- */
	vect2	&operator++();    // Prefix ++v
	vect2	operator++(int);  // Postfix v++
	vect2	&operator--();    // Prefix --v
	vect2	operator--(int);  // Postfix v--

	/* --- Access & Comparison --- */
	int		&operator[](int i);                   // For v1[1] = 12
	const int	&operator[](int i) const;         // For const v3[1]
	bool	operator==(const vect2 &other) const;
	bool	operator!=(const vect2 &other) const;
};

// To handle: scalar * vect2 (e.g., 3 * v2)
vect2
operator*(int scalar, const vect2 &v);

/* --- Output Stream --- */
std::ostream
&operator<<(std::ostream &os, const vect2 &obj);

#endif