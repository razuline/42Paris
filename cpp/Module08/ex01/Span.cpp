/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:56:11 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 18:24:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Span::Span(unsigned int N) :
	_N(N)
{
	_nums.reserve(_N);

	//std::cout << "Default constructor called" << std::endl;
}

Span::Span(const Span &copy) :
	_N(copy._N),
	_nums(copy._nums)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Span
&Span::operator=(const Span &other)
{
	if (this != &other)
	{
		this->_N = other._N;
		this->_nums = other._nums;
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

Span::~Span()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------------- METHODS -------------------------------- */

// Adds a single number to the Span.
// Throws if the Span is already full.
void
Span::addNumber(int nb)
{
	if (_nums.size() >= _N)
	{
		throw SpanFullException();
	}
	_nums.push_back(nb);
}

// Calculates the shortest span between any two numbers.
// Requires sorting to efficiently find the min difference between neighbors.
unsigned int
Span::shortestSpan()
{
	// A span requires at least two numbers to be found
	if (_nums.size() < 2)
	{
		throw NoSpanException();
	}

	std::vector<int>	sorted = _nums;
	std::sort(sorted.begin(), sorted.end()); // Standard STL algorithm

	// Start with max possible value
	unsigned int	min_diff = static_cast<unsigned int>(-1);

	for (size_t i = 0; i < sorted.size() - 1; ++i)
	{
		unsigned int
		diff = static_cast<unsigned int>(sorted[i + 1] - sorted[i]);

		if (diff < min_diff)
			min_diff = diff;
	}
	return min_diff;
}

// Calculates the longest span (max - min).
unsigned int
Span::longestSpan()
{
	if (_nums.size() < 2)
	{
		throw NoSpanException();
	}
	// Find the smallest and largest elements using STL algorithms
	int	min = *std::min_element(_nums.begin(), _nums.end());
	int	max = *std::max_element(_nums.begin(), _nums.end());

	return static_cast<unsigned int>(max - min);
}
