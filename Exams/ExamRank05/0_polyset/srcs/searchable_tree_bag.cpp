/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:17 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 14:41:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

searchable_tree_bag::searchable_tree_bag() :
	tree_bag()
{
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &copy) :
	tree_bag(copy)
{
}

searchable_tree_bag
&searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
	if (this != &other)
		tree_bag::operator=(other);
	return *this;
}

searchable_tree_bag::~searchable_tree_bag()
{
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

bool
searchable_tree_bag::has(int value_to_find) const
{
	node	*tmp = this->tree;

	// Binary Search Tree (BST) logic:
	// smaller values are on the left, larger on the right
	while (tmp != NULL)
	{
		// Found the value
		if (tmp->value == value_to_find)
			return true;

		if (value_to_find < tmp->value)
			tmp = tmp->l;
		else
			tmp = tmp->r;
	}
	// If reach here, the value is not in the tree
	return false;
}
