/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_bag.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:17:02 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:31:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** EXAM ASSIGNMENTS **************************** */
/* ************************************************************************** */

#ifndef EXAM_ASSIGNMENTS_ARRAY_BAG_HPP
# define EXAM_ASSIGNMENTS_ARRAY_BAG_HPP

# include "bag.hpp"

class array_bag :
	virtual public bag
{
protected:
	int	*data;
	int	size;

public:
	/* --- Orthodox Canonical Form --- */
	array_bag();
	array_bag(const array_bag &);
	array_bag	&operator=(const array_bag &other);
	~array_bag();

	/* --- Core Methods --- */
	void		insert(int);
	void		insert(int *, int);
	void		print() const;
	void		clear();
};


#endif