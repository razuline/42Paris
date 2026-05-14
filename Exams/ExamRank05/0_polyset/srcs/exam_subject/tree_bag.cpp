/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bag.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:31:35 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 15:24:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** EXAM ASSIGNMENTS **************************** */
/* ************************************************************************** */

#include "tree_bag.hpp"
#include <iostream>

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

tree_bag::tree_bag() :
	tree(0) // Initialise root to 0
{
	// std::cout << "Default constructor called" << std::endl;
}

tree_bag::tree_bag(const tree_bag &copy)
{
	tree = _copy_node(copy.tree);

	// std::cout << "Copy constructor called" << std::endl;
}

tree_bag
&tree_bag::operator=(const tree_bag &other)
{
	if (this != &other)
	{
		_destroy_tree(tree);
		tree = _copy_node(other.tree);
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

tree_bag::~tree_bag()
{
	_destroy_tree(tree);

	// std::cout << "Destructor called" << std::endl;
}

/* ---------------------------- PRIVATE METHODS ----------------------------- */

// defined as static functions in the class
void
tree_bag::_destroy_tree(node *curr)
{
	if (curr == 0) // Check against 0
		return;

	_destroy_tree(curr->l);
	_destroy_tree(curr->r);

	delete curr;
}

void
tree_bag::_print_node(node *curr)
{
	if (curr != 0)
	{
		_print_node(curr->l);
		if (curr->value != 0)
			std::cout << curr->value << " ";
		_print_node(curr->r);
	}
}

tree_bag::node
*tree_bag::_copy_node(node *curr)
{
	if (curr == 0) // Check against 0
		return 0;

	// Use the struct constructor or manual assignment with 0
	node	*new_n = new node;

	new_n->value = curr->value;
	new_n->l = _copy_node(curr->l);
	new_n->r = _copy_node(curr->r);

	return new_n;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

tree_bag::node
*tree_bag::extract_tree()
{
	node	*tmp = tree;

	tree = 0;
	return tmp;
}

void
tree_bag::set_tree(node *new_tree)
{
	_destroy_tree(tree);
	tree = new_tree;
}

void
tree_bag::insert(int item)
{
	node	**n = &this->tree;

	while (*n)
	{
		if (item < (*n)->value)
			n = &(*n)->l;
		else
			n = &(*n)->r;
	}
	// Initialise children to 0 for the new node
	*n = new node;
	(*n)->value = item;
	(*n)->l = 0;
	(*n)->r = 0;
}

void
tree_bag::insert(int *items, int count)
{
	for (int i = 0; i < count; i++)
		insert(items[i]);
}

void
tree_bag::print() const
{
	_print_node(tree);
	std::cout << std::endl;
}

void
tree_bag::clear()
{
	_destroy_tree(tree);
	tree = 0; // Reset root to 0
}
