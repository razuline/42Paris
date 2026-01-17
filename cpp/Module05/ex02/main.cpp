/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 13:15:03 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <ctime>
#include <cstdlib>

int	main(void)
{
	srand(time(NULL)); // Seed for robotomy randomness

	try
	{
		Bureaucrat				boss("High Level Boss", 1);
		Bureaucrat				mid("Mid Level", 45);
		Bureaucrat				intern("Intern", 150);

		ShrubberyCreationForm	f1("garden");
		RobotomyRequestForm		f2("Bender");
		PresidentialPardonForm	f3("Criminal");

		std::cout << "\n--- SHRUBBERY TEST ---" << std::endl;
		boss.signForm(f1);
		boss.executeForm(f1); // Should create garden_shrubbery file

		std::cout << "\n--- ROBOTOMY TEST ---" << std::endl;
		boss.signForm(f2);
		mid.executeForm(f2); // 50% success chance
		mid.executeForm(f2); // Execute again to see randomness

		std::cout << "\n--- PRESIDENTIAL TEST ---" << std::endl;
		boss.signForm(f3);
		intern.executeForm(f3); // Should fail (intern's grade is too low)
		boss.executeForm(f3);   // Should succeed
	}
	catch (std::exception &e)
	{
		std::cerr << "Global catch: " << e.what() << std::endl;
	}

	return 0;
}
