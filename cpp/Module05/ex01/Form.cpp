/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/05 19:17:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Form::Form(std::string name, int gradeToSign, int gradeToExec) :
	_name(name),
	_isSigned(false),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec)
{
	// Check gradeToSign limits
	if (_gradeToSign < 1)
		throw Form::GradeTooHighException();
	if (_gradeToSign > 150)
		throw Form::GradeTooLowException();

	// Check gradeToExec limits
	if (_gradeToExec < 1)
		throw Form::GradeTooHighException();
	if (_gradeToExec > 150)
		throw Form::GradeTooLowException();
	//std::cout << "Default constructor called" << std::endl;
}

Form::Form(const Form &src) :
	_name(src._name), _grade(copy._grade)
{
	//std::cout << "Copy constructor called" << std::endl;
}

Form
&Form::operator=(const Form &other)
{
	if (this != &other)
	{
		// _name is const, so we only copy the grade
		this->_grade = other._grade;
	}
	return *this;
	//std::cout << "Copy assignment operator called" << std::endl;
}

Form::~Form()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string const
Form::getName() const
{
	return _name;
}

unsigned int
Form::getGrade() const
{
	return _grade;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
Form::incrementGrade()
{
	// Promotion: numerical value decreases (e.g., 2 becomes 1)
	if (_grade - 1 < 1)
		throw Form::GradeTooHighException();
	_grade--;
}

void
Form::decrementGrade()
{
	// Demotion: numerical value increases (e.g., 149 becomes 150)
	if (_grade + 1 > 150)
		throw Form::GradeTooLowException();
	_grade++;
}

/* ------------------------------- OPERATORS -------------------------------- */

std::ostream
&operator<<(std::ostream &o, const Form &i)
{
	// Required format: <name>, bureaucrat grade <grade>
	o << i.getName() << ", bureaucrat grade " << i.getGrade() << ".";
	return o;
}
