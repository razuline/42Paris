/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/16 18:28:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"

int	main(void)
{
	// --- TEST 1: Basic Bureaucrat and Form interaction ---
	// A high-rank bureaucrat should easily sign a simple form.
	std::cout << "--- Test 1: Successful signing ---" << std::endl;
	try
	{
		Bureaucrat	boss("Zaphod", 1);
		Form		contract("Galactic Contract", 25, 50);

		std::cout << contract << std::endl;
		boss.signForm(contract); // Should print success message
		std::cout << contract << std::endl; // Show 'Yes' for signed status
	}
	catch (std::exception &e)
	{
		std::cerr << "Unexpected error: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------------------------\n" << std::endl;

	// --- TEST 2: Bureaucrat with insufficient grade ---
	// A low-rank bureaucrat trying to sign a high-level form.
	std::cout << "--- Test 2: Failed signing (Grade too low) ---" << std::endl;
	try
	{
		Bureaucrat	intern("Arthur", 150);
		Form		topSecret("Top Secret Document", 1, 1);

		std::cout << topSecret << std::endl;
		intern.signForm(topSecret); // Should print error message with reason
	}
	catch (std::exception &e)
	{
		std::cerr << "Unexpected error: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------------------------\n" << std::endl;

	// --- TEST 3: Edge Case (Exactly required grade) ---
	// According to subject, grade must be equal or higher (lower or equal).
	std::cout << "--- Test 3: Edge case (Exactly required grade) ---" << std::endl;
	try
	{
		Bureaucrat	midManager("Ford", 42);
		Form		standard("Standard Form", 42, 42);

		std::cout << midManager << std::endl;
		std::cout << "Attempting to sign with exact grade (42)..." << std::endl;
		midManager.signForm(standard); // Should succeed
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << "\n------------------------------------------\n" << std::endl;

	// --- TEST 4: Invalid Form Initialization ---
	// Testing if Form constructor throws exceptions for invalid grades.
	std::cout << "--- Test 4: Invalid Form creation ---" << std::endl;
	try
	{
		Form	impossible("Impossible Form", 0, 151);
	}
	catch (std::exception &e)
	{
		std::cout << "Caught expected exception during creation: "
				  << e.what() << std::endl;
	}

	return 0;
}
