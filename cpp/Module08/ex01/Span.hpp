/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:56:21 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 13:07:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

class Span
{
private:
	const unsigned int	_N;

public:
	// --- Orthodox Canonical Form ---
	Span(const unsigned int N);
	Span(const Span &copy);
	Span	&operator=(const Span &other);
	~Span();

	/* --- Methods --- */

	/* --- Custom Exception Class --- */
};

#endif