/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:20 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/05 15:12:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Bureaucrat::Bureaucrat(std::string name, int grade) :
	_name(name)
{
	// Check if grade is within range 1-150
	if (grade < 1)
	{
		throw Bureaucrat::GradeTooHighException(); // Starts alert
	}
	if (grade > 150)
	{
		throw Bureaucrat::GradeTooLowException(); // Starts alert
	}
	_grade = grade;
	//std::cout << "Default constructor called" << std::endl;
}

Bureaucrat::Bureaucrat(const Bureaucrat &copy) :
	_name(copy._name), _grade(copy._grade)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Bureaucrat
&Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		// _name is const, so we only copy the grade
		this->_grade = other._grade;
	}
	return *this;
	//std::cout << "Copy assignment operator called" << std::endl;
}

Bureaucrat::~Bureaucrat()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string const
Bureaucrat::getName() const
{
	return _name;
}

unsigned int
Bureaucrat::getGrade() const
{
	return _grade;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Bureaucrat::incrementGrade()
{
	// Promotion: numerical value decreases (e.g., 2 becomes 1)
	if (_grade - 1 < 1)
		throw Bureaucrat::GradeTooHighException();
	_grade--;
}

void
Bureaucrat::decrementGrade()
{
	// Demotion: numerical value increases (e.g., 149 becomes 150)
	if (_grade + 1 > 150)
		throw Bureaucrat::GradeTooLowException();
	_grade++;
}

/* ------------------------------- OPERATORS -------------------------------- */

std::ostream
&operator<<(std::ostream &o, const Bureaucrat &i)
{
	// Required format: <name>, bureaucrat grade <grade>
	o << i.getName() << ", bureaucrat grade " << i.getGrade() << ".";
	return o;
}
