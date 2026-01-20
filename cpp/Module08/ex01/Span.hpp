/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:56:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 18:31:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <algorithm>
# include <exception>
# include <vector>

class Span
{
private:
	unsigned int		_N;    // Max number of int the span can store
	std::vector<int>	_nums; // Internal container to store int

public:
	// --- Orthodox Canonical Form ---
	Span(unsigned int N);
	Span(const Span &copy);
	Span	&operator=(const Span &other);
	~Span();

	/* --- Mandatory Methods --- */
	void			addNumber(int nb);
	unsigned int	shortestSpan();
	unsigned int	longestSpan();

	/* --- Range of Iterators Method --- */
	// Adds multiple numbers using a range of iterators
	template <typename T>
	void	addNumbers(T begin, T end)
	{
		// Check if the range fits within the remaining capacity
		if (std::distance(begin, end) + _nums.size() > _N)
			throw std::out_of_range("Span is full");
		_nums.insert(_nums.end(), begin, end);
	}

	/* --- Exceptions --- */
	class SpanFullException : public std::exception
	{
		virtual const char	*what() const throw()
		{
			return "Span is already full";
		}
	};

	class NoSpanException : public std::exception
	{
		virtual const char	*what() const throw()
		{
			return "Not enough numbers to find a span";
		}
	};
};

#endif