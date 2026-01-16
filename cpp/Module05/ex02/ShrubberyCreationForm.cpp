/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:29:38 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 19:16:08 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

ShrubberyCreationForm::
ShrubberyCreationForm(const std::string &target) :
	AForm("ShrubberyCreationForm", 145, 137),
	_target(target)
{
	//std::cout << "Default constructor called" << std::endl;
}

ShrubberyCreationForm::
ShrubberyCreationForm(const ShrubberyCreationForm &src) :
	AForm(src),
	_target(src._target)
{
	//std::cout << "Copy constructor called" << std::endl;
}

ShrubberyCreationForm
&ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
	if (this != &other)
	{
		AForm::operator=(other);
	}
	return *this;

	//std::cout << "Copy assignment operator called" << std::endl;
}

ShrubberyCreationForm::
~ShrubberyCreationForm()
{
	//std::cout << "Destructor called" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
ShrubberyCreationForm::execute(Bureaucrat const &executor) const
{
	this->checkExecutability(executor);

	std::string		filename = _target + "_shrubbery";
	std::ofstream	outFile(filename.c_str());

	if (!outFile.is_open())
	{
		return;
	}

	outFile << "      /\\      " << std::endl;
	outFile << "     /\\*\\     " << std::endl;
	outFile << "    /\\O\\*\\    " << std::endl;
	outFile << "   /*/\\/\\/\\   " << std::endl;
	outFile << "  /\\O\\/\\*\\/\\  " << std::endl;
	outFile << "      ||      " << std::endl;

	outFile.close();
}
