/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 12:56:11 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/20 13:08:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Span::Span(const unsigned int N) :
	_N(6)
{
	//std::cout << "Default constructor called" << std::endl;
}

Span::Span(const Span &copy) :
	_N(copy._N)
{


	//std::cout << "Copy constructor called" << std::endl;
}

Span
&Span::operator=(const Span &other)
{



	//std::cout << "Copy assignment operator called" << std::endl;
}

Span::~Span()
{


	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------------- METHODS -------------------------------- */


