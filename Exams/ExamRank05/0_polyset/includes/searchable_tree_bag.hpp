/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:20 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 21:01:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEARCHABLE_TREE_BAG_HPP
# define SEARCHABLE_TREE_BAG_HPP

# include "tree_bag.hpp"
# include "searchable_bag.hpp"

# include <iostream>

class searchable_tree_bag :
	public tree_bag,
	public searchable_bag
{
public:
	/* --- Orthodox Canonical Form --- */
	searchable_tree_bag();
	searchable_tree_bag(const searchable_tree_bag &copy);
	searchable_tree_bag	&operator=(const searchable_tree_bag &other);
	virtual	~searchable_tree_bag();

	/* --- Core Methods --- */
	virtual bool	has(int value) const;
};

#endif