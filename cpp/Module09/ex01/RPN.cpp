/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:13:42 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/07 18:34:52 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

RPN::RPN()
{
	//std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(const RPN &copy)
{
	(void)copy;

	//std::cout << "Copy constructor called" << std::endl;
}

RPN
&RPN::operator=(const RPN &other)
{
	(void)other;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

RPN::~RPN()
{
	//std::cout << "Destructor called" << std::endl;
}

/* -------------------------------- METHODS --------------------------------- */

void
RPN::calculate(const std::string &expression)
{

}
