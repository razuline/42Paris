/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:30:22 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:26:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

RobotomyRequestForm::
RobotomyRequestForm(const std::string &target) :
	AForm("RobotomyRequestForm", 75, 45),
	_target(target)
{
	//std::cout << "Default constructor called" << std::endl;
}

RobotomyRequestForm::
RobotomyRequestForm(const RobotomyRequestForm &src) :
	AForm(src),
	_target(src._target)
{
	//std::cout << "Copy constructor called" << std::endl;
}

RobotomyRequestForm
&RobotomyRequestForm::operator=(const RobotomyRequestForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

RobotomyRequestForm::
~RobotomyRequestForm()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
RobotomyRequestForm::execute(Bureaucrat const &executor) const
{
	this->checkExecutability(executor);

	std::cout << "* BZZZZZZ... DRILLING NOISES... VZZZZZZ *" << std::endl;

	// 50% success chance logic
	if (rand() % 2 == 0)
	{
		std::cout << _target << " has been robotomized successfully!"
				  << std::endl;
	}
	else
	{
		std::cout << "The robotomy on " << _target << " failed." << std::endl;
	}
}
