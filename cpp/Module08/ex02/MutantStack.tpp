/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:32:03 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/27 22:50:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANT_STACK_TPP
# define MUTANT_STACK_TPP

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

// Default constructor: calls the base std::stack constructor
template <typename T>
MutantStack<T>::MutantStack() :
	std::stack<T>()
{
	// std::cout << "Default constructor called" << std::endl;
}

// Copy constructor: initialises the base stack with another MutantStack
template <typename T>
MutantStack<T>::MutantStack(const MutantStack<T> &copy) :
	std::stack<T>(copy)
{
	// std::cout << "Copy constructor called" << std::endl;
}

// Assignment operator: utilises the base stack's assignment logic
template <typename T>
MutantStack<T>
&MutantStack<T>::operator=(const MutantStack<T> &other)
{
	if (this != &other)
		std::stack<T>::operator=(other);
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

// Destructor: virtual by inheritance from std::stack
template <typename T>
MutantStack<T>::~MutantStack()
{
	// std::cout << "Destructor called" << std::endl;
}

/* --------------------------------- METHODS -------------------------------- */

// Accessing the underlying container 'c'.
// 'c' is a protected member of std::stack, accessible only through inheritance.
template <typename T>
typename MutantStack<T>::
iterator MutantStack<T>::begin()
{
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::
const_iterator MutantStack<T>::begin() const
{
	return this->c.begin();
}

template <typename T>
typename MutantStack<T>::
iterator MutantStack<T>::end()
{
	return this->c.end();
}

template <typename T>
typename MutantStack<T>::
const_iterator MutantStack<T>::end() const
{
	return this->c.end();
}

// Returns a reverse iterator to the element following the last element
template <typename T>
typename MutantStack<T>::
reverse_iterator MutantStack<T>::rbegin()
{
	// Returns a reverse iterator to the beginning
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::
const_reverse_iterator MutantStack<T>::rbegin() const
{
	return this->c.rbegin();
}

template <typename T>
typename MutantStack<T>::
reverse_iterator MutantStack<T>::rend()
{
	// Returns a reverse iterator to the end
	return this->c.rend();
}

template <typename T>
typename MutantStack<T>::
const_reverse_iterator MutantStack<T>::rend() const
{
	return this->c.rend();
}

#endif