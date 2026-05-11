/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2_exam.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:34:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/11 17:43:06 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_EXAM_HPP
# define VECT2_EXAM_HPP

# include <iostream>

class vect2
{
private:
	int			_x;
	int			_y;

public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &copy);
	vect2		&operator=(const vect2 &other);
	~vect2();

	vect2		&operator+=(const vect2 &other);
	vect2		operator+(const vect2 &other) const;

	vect2		&operator-=(const vect2 &other);
	vect2		operator-(const vect2 &other) const;
	vect2		operator-() const;

	vect2		&operator++();
	vect2		operator++(int);
	vect2		&operator--();
	vect2		operator--(int);

	vect2		&operator*=(int scalar);
	vect2		operator*(int scalar) const;

	bool		operator==(const vect2 &other) const;
	bool		operator!=(const vect2 &other) const;

	int			&operator[](int i);
	const int	&operator[](int i) const;
};

vect2
operator*(int scalar, const vect2 &v);

std::ostream
&operator<<(std::ostream &os, const vect2 &v);

#endif