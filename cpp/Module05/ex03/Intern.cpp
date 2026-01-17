/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 13:35:00 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 14:19:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Intern::Intern()
{
	//std::cout << "Default constructor called" << std::endl;
}

Intern::Intern(const Intern &src)
{
	(void)src;

	//std::cout << "Copy constructor called" << std::endl;
}

Intern
&Intern::operator=(const Intern &other)
{
	(void)other;
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

Intern::~Intern()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

AForm
*Intern::createShrubbery(std::string target)
{
	return new ShrubberyCreationForm(target);
}

AForm
*Intern::createRobotomy(std::string target)
{
	return new RobotomyRequestForm(target);
}

AForm
*Intern::createPardon(std::string target)
{
	return new PresidentialPardonForm(target);
}

// makeForm uses an array of strings and an array of function pointers.
// This is a clean implementation of the "Factory" design pattern.
AForm
*Intern::makeForm(std::string name, std::string target)
{
	// Valid form names in an array for easy iteration
	std::string	names[] =
	{
		"shrubbery creation",
		"robotomy request",
		"presidential pardon"
	};

	// Array of pointers to static member functions
	AForm	*(*creators[])(std::string) =
	{
		&createShrubbery,
		&createRobotomy,
		&createPardon
	};

	for (int i = 0; i < 3; i++)
	{
		if (name == names[i])
		{
			// Successfully found the form type
			std::cout << "Intern creates " << name << std::endl;
			return creators[i](target);
		}
	}

	// If the loop finished without returning, the name is invalid
	std::cout << "Error: Intern cannot create form '" << name << "'."
			  << std::endl;

	return NULL;
}
