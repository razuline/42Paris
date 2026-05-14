/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_bag.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 19:12:54 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 15:06:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* **************************** EXAM ASSIGNMENTS **************************** */
/* ************************************************************************** */

#ifndef EXAM_ASSIGNMENTS_TREE_BAG_HPP
# define EXAM_ASSIGNMENTS_TREE_BAG_HPP

# include "bag.hpp"

class tree_bag :
	virtual public bag
{
protected:
	// binary serach tree node
	struct node
	{
		node	*l;
		node	*r;
		int		value;
	};

	node	*tree; // root node

private:
	/* --- Private Helper Methods --- */
	static void		_destroy_tree(node *);
	static void		_print_node(node *);
	static node		*_copy_node(node *); // void* -> node*

public:
	/* --- Orthodox Canonical Form --- */
	tree_bag();
	tree_bag(const tree_bag &);
	tree_bag		&operator=(const tree_bag &);
	~tree_bag();

	/* --- Core Methods --- */
	node			*extract_tree(); // getter
	void			set_tree(node *);

	virtual void	insert(int);
	virtual void	insert(int *items, int count);
	virtual void	print() const;
	virtual void	clear();
};

#endif