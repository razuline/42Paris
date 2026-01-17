/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 14:13:50 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>

int	main(void)
{
	// Seed for random numbers (needed for Robotomy 50/50 chance)
	std::srand(std::time(NULL));

	Intern		someRandomIntern;
	Bureaucrat	boss("The Boss", 1);       // Can sign and execute anything
	Bureaucrat	intern("The Intern", 150); // Can't sign or execute anything
	AForm*		form;

	std::cout << "--- TEST 1: ROBOTOMY REQUEST ---" << std::endl;
	// Successful creation
	form = someRandomIntern.makeForm("robotomy request", "Bender");
	if (form)
	{
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form; // IMPORTANT: Always delete form returned by Intern
	}

	std::cout << "\n--- TEST 2: SHRUBBERY CREATION ---" << std::endl;
	form = someRandomIntern.makeForm("shrubbery creation", "Home");
	if (form)
	{
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	std::cout << "\n--- TEST 3: PRESIDENTIAL PARDON ---" << std::endl;
	form = someRandomIntern.makeForm("presidential pardon", "Criminal");
	if (form)
	{
		boss.signForm(*form);
		boss.executeForm(*form);
		delete form;
	}

	std::cout << "\n--- TEST 4: ERROR CASE (Low Grade) ---" << std::endl;
	form = someRandomIntern.makeForm("presidential pardon", "Unlucky");
	if (form)
	{
		intern.signForm(*form);    // Should fail
		intern.executeForm(*form); // Should fail
		delete form;
	}

	std::cout << "\n--- TEST 5: INVALID FORM NAME ---" << std::endl;
	// Intern should return NULL and not crash
	form = someRandomIntern.makeForm("coffee request", "Kitchen");
	if (form)
	{
		delete form;
	}
	else
	{
		std::cout << "Correct: Intern couldn't create an unknown form."
				  << std::endl;
	}

	return 0;
}
