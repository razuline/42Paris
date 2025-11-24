/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:21:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:32:04 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

// Constructor: Initialises the ideas to avoid random garbage values.
Brain::Brain(void)
{
	std::cout << "Brain constructor called..." << std::endl;
	for (int i = 0; i < 100; i++)
		_ideas[i] = "default idea";
}

// Copy Constructor: Performs a deep copy of the ideas array.
Brain::Brain(const Brain &copy)
{
	std::cout << "Brain copy constructor called..." << std::endl;
	for (int i = 0; i < 100; i++)
		this->_ideas[i] = copy._ideas[i]; // Copy each string individually
}

// Assignment Operator: Same logic as copy constructor.
Brain
&Brain::operator=(const Brain &other)
{
	std::cout << "Brain assignment operator called..." << std::endl;
	if (this != &other) // Self-assignment check
	{
		for (int i = 0; i < 100; i++)
			this->_ideas[i] = other._ideas[i];
	}
	return *this;
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor called..." << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string
Brain::getIdea(int idx) const
{
	if (idx >= 0 && idx < 100)
		return _ideas[idx];
	return "";
}

void
Brain::setIdea(int idx, const std::string &idea)
{
	if (idx >= 0 && idx < 100)
		_ideas[idx] = idea;
}
