/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:15:20 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 16:56:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main(void) {
	// A string variable
	std::string	str = "HI THIS IS BRAIN";
	// Un pointeur qui pointe vers l'adresse de cette string
	std::string	*stringPTR = &str;
	// Une référence qui référence cette même string
	std::string	&stringREF = str;

/* ----------------------------- MEMORY ADDRESS ----------------------------- */

	// L'adresse de la variable string
	std::cout << "Memory address of the string variable: " << &str << std::endl;
	// L'adresse contenue dans le pointeur
	std::cout << "Memory address held by stringPTR:      " << stringPTR
			<< std::endl;
	// L'adresse de la référence
	std::cout << "Memory address held by stringREF:      " << &stringREF
			<< std::endl;

	/* Elles sont identiques */

/* ---------------------------------- VALUE --------------------------------- */

	// La valeur de la variable string
	std::cout << "Value of the string variable:          " << str << std::endl;
	// La valeur pointée par le pointeur
	std::cout << "Value pointed to by stringPTR:         " << *stringPTR
			<< std::endl;
	// La valeur de la référence
	std::cout << "Value pointed to by stringREF:         " << stringREF
			<< std::endl;

	/* Elles seront identiques aussi */
}











