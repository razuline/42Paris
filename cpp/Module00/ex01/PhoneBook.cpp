/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 13:29:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/01 14:30:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

void	PhoneBook::addContact(void) {
	Contact		newContact;
	std::string	userInput;

	// _firstname
	while (true) {
		std::cout << "Enter your first name: ";
		std::getline(std::cin, userInput);
		if (newContact.setFirstname(userInput) == true)
			break;
		else
			std::cout << "Error: Enter only letters." << std::endl;
	}

	// _lastname
	while (true) {
		
		std::cout << "Enter your last name: ";
		std::getline(std::cin, userInput);
		if (newContact.setLastname(userInput) == true)
			break;
		else
			std::cout << "Error: Enter only letters." << std::endl;
	}

	// _nickname
	while (true) {
		std::cout << "Enter your nickname: ";
		std::getline(std::cin, userInput);
		if (newContact.setNickname(userInput) == true)
			break;
		else
			std::cout << "Error: Enter only letters." << std::endl;
	}

	// _number
	while (true) {
		std::cout << "Enter your phone number: ";
		std::getline(std::cin, userInput);
		if (newContact.setNumber(userInput) == true)
			break;
		else
			std::cout << "Error: Enter only digits." << std::endl;
	}

	// _secret
	while (true) {
		std::cout << "Enter your darkest secret: ";
		std::getline(std::cin, userInput);
		if (newContact.setSecret(userInput) == true)
			break;
		else
			std::cout << "Error: Enter only letters." << std::endl;
	}
	this->_contacts[this->_contactIndex] = newContact;
	this->_contactIndex = (this->_contactIndex + 1) % 8;
}

void	PhoneBook::searchContact(void) const {
	// Affiche l'en-tête
	std::cout << "|----------|----------|----------|----------|" << std::endl;
	std::cout << "|     index|first name| last name|  nickname|" << std::endl;
	std::cout << "|----------|----------|----------|----------|" << std::endl;

	for (int i = 0; i < 8; i++) {
		// Colonne Index
		std::cout << "|" << std::setw(10) << i;

		// Colonne First name
		i = 0;
		std::string	firstname = this->_contacts[i].getFirstname();
		if (firstname.length() > 10)
			firstname = firstname.substr(0, 9) + ".";
		std::cout << "|" << std::setw(10) << firstname;

		// Colonne Last name
		i = 0;
		std::string	lastname = this->_contacts[i].getLastname();
		if (lastname.length() > 10)
			lastname = lastname.substr(0, 9) + ".";
		std::cout << "|" << std::setw(10) << lastname;

		// Colonne Nickname
		i = 0;
		std::string	nickname = this->_contacts[i].getNickname();
		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";
		std::cout << "|" << std::setw(10) << nickname << "|" << std::endl;
	}
	std::cout << "|----------|----------|----------|----------|" << std::endl;
}
