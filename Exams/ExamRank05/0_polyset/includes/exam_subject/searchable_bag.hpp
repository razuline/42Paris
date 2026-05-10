/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_bag.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:23:19 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:32:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** EXAM ASSIGNMENTS **************************** */
/* ************************************************************************** */

#ifndef EXAM_ASSIGNMENTS_SORTABLE_HPP
# define EXAM_ASSIGNMENTS_SORTABLE_HPP

# include "bag.hpp"

class searchable_bag :
	virtual public bag
{
public:
	/* --- Core Methods --- */
	virtual bool	has(int) const = 0;
};

#endif