/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bag.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:31:35 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 20:36:30 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree_bag.hpp"
#include <iostream>

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

tree_bag::tree_bag() :
	tree(0)
{
	// std::cout << "Default constructor called" << std::endl;
}

tree_bag::tree_bag(const tree_bag &copy)
{
	this->tree = _copy_node(copy.tree);

	// std::cout << "Copy constructor called" << std::endl;
}

tree_bag
&tree_bag::operator=(const tree_bag &other)
{
	this->clear();
	this->tree = _copy_node(other.tree);

	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

tree_bag::~tree_bag()
{
	this->_destroy_tree(this->tree);

	// std::cout << "Destructor called" << std::endl;
}

/* ---------------------------- PRIVATE METHODS ----------------------------- */

void
tree_bag::_destroy_tree(node *n)
{
	if (!n)
		return;

	_destroy_tree(n->l);
	_destroy_tree(n->r);

	delete(n);
}

void
tree_bag::_print_node(node *n)
{
	if (!n)
		return;

	_print_node(n->l);
	std::cout << n->value << " ";
	_print_node(n->r);
}

tree_bag::node
*tree_bag::_copy_node(node *n)
{
	if (!n)
		return 0;

	return new node((node){_copy_node(n->l), _copy_node(n->r), n->value});
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

tree_bag::node
*tree_bag::extract_tree()
{
	node	*ret = this->tree;

	this->tree = 0;

	return ret;
}

void
tree_bag::set_tree(node *t)
{
	_destroy_tree(this->tree);
	this->tree = t;
}

void
tree_bag::insert(int val)
{
	node	**n = &this->tree;

	while (*n)
	{
		if (val < (*n)->value)
			n = &(*n)->l;
		else if (val >= (*n)->value)
			n = &(*n)->r;
	}
	*n = new node((node){0, 0, val});
}

void
tree_bag::insert(int *array, int size)
{
	for (int i = 0; i < size; i++)
		this->insert(array[i]);
}

void
tree_bag::print() const
{
	this->_print_node(this->tree);
	std::cout << std::endl;
}

void
tree_bag::clear()
{
	this->_destroy_tree(this->tree);
	this->tree = NULL;
}
