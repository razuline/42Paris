/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect2_exam.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 14:34:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/13 14:54:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT2_EXAM_HPP
# define VECT2_EXAM_HPP

# include <iostream>

class vect2
{
private:
	int		_x;
	int		_y;

public:
	vect2();
	vect2(int x, int y);
	vect2(const vect2 &copy);
	vect2	&operator=(const vect2 &other);
	~vect2();

	vect2	&operator+=(const vect2 &other);
	vect2	operator+(const vect2 &other) const;

	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);

	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);

	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);

	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
	vect2	&operator=(const vect2 &other);
}

#endif