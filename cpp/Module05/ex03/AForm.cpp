/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 17:10:56 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 18:42:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

AForm::AForm(std::string name, int gradeToSign, int gradeToExec) :
	_name(name),
	_isSigned(false),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec)
{
	// Check gradeToSign limits
	if (_gradeToSign < 1)
		throw AForm::GradeTooHighException();
	if (_gradeToSign > 150)
		throw AForm::GradeTooLowException();

	// Check gradeToExec limits
	if (_gradeToExec < 1)
		throw AForm::GradeTooHighException();
	if (_gradeToExec > 150)
		throw AForm::GradeTooLowException();

	//std::cout << "Default constructor called" << std::endl;
}

AForm::AForm(const AForm &src) :
	_name(src._name),
	_isSigned(src._isSigned),
	_gradeToSign(src._gradeToSign),
	_gradeToExec(src._gradeToExec)
{
	//std::cout << "Copy constructor called" << std::endl;
}

AForm
&AForm::operator=(const AForm &other)
{
	if (this != &other)
	{
		// Only _isSigned can be copied, others are const
		this->_isSigned = other._isSigned;
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

AForm::~AForm()
{
	//std::cout << "Destructor called" << std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

std::string const
AForm::getName() const
{
	return _name;
}

bool
AForm::getIsSigned() const
{
	return _isSigned;
}

unsigned int
AForm::getGradeToSign() const
{
	return _gradeToSign;
}

unsigned int
AForm::getGradeToExec() const
{
	return _gradeToExec;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
AForm::beSigned(const Bureaucrat &b)
{
	// b.getGrade(): bureaucrat's grade
	// this->getGradeToSign(): requires to this form's grade
	if (b.getGrade() > _gradeToSign)
	{
		throw AForm::GradeTooLowException();
	}
	_isSigned = true;
}

void
AForm::checkExecutability(Bureaucrat const &executor) const
{
	if (!this->getIsSigned())
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > this->getGradeToExec())
		throw AForm::GradeTooLowException();
}

/* --------------------------- INSERTION OPERATOR --------------------------- */

std::ostream
&operator<<(std::ostream &out, const AForm &b)
{
	out << "Form " << b.getName()
	  << "(signed: " << (b.getIsSigned() ? "yes" : "no")
	  << ", sign grade: " << b.getGradeToSign()
	  << ", exec grade: " << b.getGradeToExec() << ")";

	return out;
}
