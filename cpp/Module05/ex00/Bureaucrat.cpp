/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:20 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/03 14:53:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Bureaucrat::Bureaucrat(std::string name) :
	_name(name)
{
	this->_name;
	std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy) :
	_name(copy._name), _grade(copy._grade)
{
	std::cout << "Copy constructor called" << std::endl;
}

Bureaucrat
&Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		this->_grade = other._grade;
	}
	return *this;
	std::cout << "Copy assignment operator called" << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Destructor called" << std::endl;
}
