/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 18:29:38 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:25:26 by erazumov         ###   ########.fr       */
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
	// 1. Verify if execution is possible (throws exception if not)
	this->checkExecutability(executor);

	// 2. File creation logic using the target provided in constructor
	std::string		filename = _target + "_shrubbery";
	std::ofstream	outFile(filename.c_str());

	if (!outFile.is_open())
	{
		std::cerr << "Error: Could not create file " << filename << std::endl;
		return;
	}

	// 3. Drawing the ASCII tree inside the file
	outFile << "      /\\      " << std::endl;
	outFile << "     /\\*\\     " << std::endl;
	outFile << "    /\\O\\*\\    " << std::endl;
	outFile << "   /*/\\/\\/\\   " << std::endl;
	outFile << "  /\\O\\/\\*\\/\\  " << std::endl;
	outFile << "      ||      " << std::endl;

	outFile.close();
}
