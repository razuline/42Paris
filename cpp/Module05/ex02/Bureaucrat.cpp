/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:20 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 18:28:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

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
	_name(copy._name),
	_grade(copy._grade)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Bureaucrat
&Bureaucrat::operator=(const Bureaucrat &other)
{
	if (this != &other)
	{
		// _name is const, so we only copy _grade
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

void
Bureaucrat::signForm(AForm &f)
{
	try
	{
		// Attempt to sign the form
		f.beSigned(*this);
		// Success message
		std::cout << _name << " signed " << f.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		// Error message if grade is too low
		std::cout << _name << " couldn't sign " << f.getName()
				  << " because " << e.what() << std::endl;
	}
}

/* --------------------------- INSERTION OPERATOR --------------------------- */

std::ostream
&operator<<(std::ostream &out, const Bureaucrat &b)
{
	// Required format: <name>, bureaucrat grade <grade>
	out << b.getName()
		<< ", bureaucrat grade "
		<< b.getGrade() << ".";

	return out;
}
