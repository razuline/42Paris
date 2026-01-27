/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:31:53 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/27 22:48:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

# include <stack>

/* ---------------------------------- CLASS --------------------------------- */

// MutantStack inherited from std::stack to make it iterable.
// std::stack is a container adapter that wraps
// a sequence container (default: std::deque).
template <typename T>
class MutantStack : public std::stack<T>
{
public:
	/* --- Orthodox Canonical Form --- */
	MutantStack();
	MutantStack(const MutantStack<T> &copy);
	MutantStack	&operator=(const MutantStack<T> &other);
	~MutantStack();

	/* --- Iterator Aliases --- */
	// Reach into the underlying container 'c' of std::stack.
	// container_type: member of std::stack referring to the wrapped container.
	typedef typename std::stack<T>::
		container_type::iterator iterator;
	typedef typename std::stack<T>::
		container_type::const_iterator const_iterator;
	typedef typename std::stack<T>::
		container_type::reverse_iterator reverse_iterator;
	typedef typename std::stack<T>::
		container_type::const_reverse_iterator const_reverse_iterator;

	/* --- Methods --- */
	// Returns an iterator to the beginning of the underlying container 'c'
	iterator				begin();
	const_iterator			begin() const;

	// Returns an iterator to the end of the underlying container 'c'
	iterator				end();
	const_iterator			end() const;

	// Reverse Iterator Methods
	reverse_iterator		rbegin();
	const_reverse_iterator	rbegin() const;
	reverse_iterator		rend();
	const_reverse_iterator	rend() const;
};

# include "MutantStack.tpp"

#endif