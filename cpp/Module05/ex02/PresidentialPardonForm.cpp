/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:30:47 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:04:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

PresidentialPardonForm::
PresidentialPardonForm(const std::string &target) :
	AForm("PresidentialPardonForm", 25, 5),
	_target(target)
{
	//std::cout << "Default constructor called" << std::endl;
}

PresidentialPardonForm::
PresidentialPardonForm(const PresidentialPardonForm &src) :
	AForm(src),
	_target(src._target)
{
	//std::cout << "Copy constructor called" << std::endl;
}

PresidentialPardonForm
&PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

PresidentialPardonForm::
~PresidentialPardonForm()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
	this->checkExecutability(executor);

	std::cout << _target << " has been pardoned by Zaphod Beeblebrox."
			  << std::endl;
}
