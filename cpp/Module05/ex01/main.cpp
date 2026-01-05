/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:06:12 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/05 15:24:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	// --- TEST 1: Valid initialisation ---
	// Verifying that a bureaucrat is created correctly with valid parameters.
	// The grade must be between 1 and 150.
	std::cout << "--- Test 1: Valid initialisation ---" << std::endl;
	try
	{
		Bureaucrat	b1("Alice", 2);
		// Uses the overloaded << operator
		std::cout << b1 << std::endl; // Alice, bureaucrat grade 2.
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// --- TEST 2: Grade too high at creation ---
	// Grade 1 is the highest possible. 0 is out of bounds.
	// Must throw GradeTooHighException.
	std::cout << "--- Test 2: Grade too high (0) ---" << std::endl;
	try
	{
		Bureaucrat	b2("Boss", 0);
	}
	catch (std::exception &e)
	{
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// --- TEST 3: Grade too low at creation ---
	// Grade 150 is the lowest possible. 151 is out of bounds.
	// Must throw GradeTooLowException.
	std::cout << "--- Test 3: Grade too low (151) ---" << std::endl;
	try
	{
		Bureaucrat	b3("Intern", 151);
	}
	catch (std::exception &e)
	{
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// --- TEST 4: Promotion and high limit exception ---
	// Incrementing means getting closer to grade 1.
	// Attempting to go above grade 1 must throw an exception.
	std::cout << "--- Test 4: Incrementing grade 2 -> 1 -> Exception ---" << std::endl;
	try
	{
		Bureaucrat	b4("Promotion", 2);
		std::cout << "Initial: " << b4 << std::endl;
		b4.incrementGrade();
		std::cout << "After increment: " << b4 << std::endl;
		b4.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// --- TEST 5: Demotion and low limit exception ---
	// Decrementing means getting closer to grade 150.
	// Attempting to go below grade 150 must throw an exception.
	std::cout << "--- Test 5: Decrementing grade 149 -> 150 -> Exception ---" << std::endl;
	try
	{
		Bureaucrat	b5("Demotion", 149);
		std::cout << "Initial: " << b5 << std::endl;
		b5.decrementGrade();
		std::cout << "After decrement: " << b5 << std::endl;
		b5.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cerr << "Caught expected error: " << e.what() << std::endl;
	}

	std::cout << std::endl;

	// --- TEST 6: Orthodox Canonical Form (Copy independence) ---
	// Ensuring that classes from Module 02 onwards follow OCF.
	// Testing that the copy constructor creates a truly independent object.
	std::cout << "--- Test 6: Orthodox Canonical Form (Copy) ---" << std::endl;
	try
	{
		Bureaucrat	original("Original", 42);
		Bureaucrat	copy(original); // Testing Copy Constructor
		
		std::cout << "Original: " << original << std::endl;
		std::cout << "Copy: " << copy << std::endl;
		
		original.incrementGrade(); // Only the original should change
		std::cout << "Original after promo: " << original << std::endl;
		std::cout << "Copy (should be unchanged): " << copy << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
