/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 15:25:11 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 15:43:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

ScalarConverter::ScalarConverter()
{
	//std::cout << "Default constructor called" << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;

	//std::cout << "Copy constructor called" << std::endl;
}

ScalarConverter
&ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

ScalarConverter::~ScalarConverter()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string const
ScalarConverter::getName() const
{
	return _name;
}

unsigned int
ScalarConverter::getGrade() const
{
	return _grade;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
ScalarConverter::convert(const std::string &literal)
{
	
}
