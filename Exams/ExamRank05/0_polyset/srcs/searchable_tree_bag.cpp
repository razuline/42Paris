/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchable_tree_bag.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:42:17 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 21:01:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "searchable_tree_bag.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

searchable_tree_bag::searchable_tree_bag() :
	tree_bag()
{
	// std::cout << "Default constructor called" << std::endl;
}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag &copy) :
	tree_bag(copy)
{
	// std::cout << "Copy constructor called" << std::endl;
}

searchable_tree_bag
&searchable_tree_bag::operator=(const searchable_tree_bag &other)
{
	if (this != &other)
	{
		tree_bag::operator=(other);
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

searchable_tree_bag::~searchable_tree_bag()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

bool
searchable_tree_bag::has(int value_to_find) const
{
	// Can access 'node' and 'tree' because we are inside a member function
	// of a class that inherits from tree_bag.
	node	*tmp = this->tree;

	while (tmp != NULL)
	{
		// Found the value
		if (tmp->value == value_to_find)
			return true;

		// Binary Search logic:
		// If the target is smaller, go left. Otherwise, go right.
		if (value_to_find < tmp->value)
			tmp = tmp->l;
		else
			tmp = tmp->r;
	}
	// If reach here, the value is not in the tree
	return false;
}
