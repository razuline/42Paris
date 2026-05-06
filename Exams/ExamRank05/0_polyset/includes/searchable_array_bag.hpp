/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_array_bag.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:41:59 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:36:09 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_ARRAY_BAG_HPP
# define SEARCHABLE_ARRAY_BAG_HPP

# include "array_bag.hpp"
# include "searchable_bag.hpp"

// This class combines array storage with search capability
class searchable_array_bag :
	public array_bag,
	public searchable_bag
{
public:
	/* --- Orthodox Canonical Form --- */
	searchable_array_bag();
	searchable_array_bag(const searchable_array_bag &copy);
	searchable_array_bag	&operator=(const searchable_array_bag &other);
	virtual	~searchable_array_bag();

	/* --- Core Methods --- */
	// Check if a value exists in the underlying array
	virtual bool	has(int value) const;
};

#endif