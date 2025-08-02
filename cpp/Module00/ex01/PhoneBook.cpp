/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:24:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/08/02 12:39:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PhoneBook.hpp"

PhoneBook::PhoneBook(void)
{
	this->_index = 0;
	this->_contact_count = 0;
}

void	PhoneBook::addContact()
{
	std::cin.ignore();
	std::string	firstName, lastName, nickname, phoneNumber, secret;

	std::cout << "Enter your name: ";
	std::getline(std::cin, firstName);

	std::cout << "Enter your last name: ";
	std::getline(std::cin, lastName);

	std::cout << "Enter your nickname: ";
	std::getline(std::cin, nickname);

	std::cout << "Enter your phone number: ";
	std::getline(std::cin, phoneNumber);

	std::cout << "Enter your darkest secret: ";
	std::getline(std::cin, secret);

	_contacts[_index].setFirstName(firstName);
	_contacts[_index].setLastName(lastName);
	_contacts[_index].setNickname(nickname);
	_contacts[_index].setPhoneNumber(phoneNumber);
	_contacts[_index].setSecret(secret);

	std::cout << "Contact ajouté !" << std::endl;
	_index = (_index + 1) % 8;
	if (this->_contact_count < 8)
		this->_contact_count++;
}

void	PhoneBook::searchContact()
{
	std::cout << "|     index|first name| last name|  nickname|" << std::endl;

	for (int i = 0; i < 8; i++)
	{
		// Column INDEX
		std::cout << "|" << std::setw(10) << i << "|";

		// Column FIRST NAME
		std::string	firstName = _contacts[i].getFirstName();
		if (firstName.length() > 10)
			firstName = firstName.substr(0, 9) + ".";
		std::cout << std::setw(10) << firstName << "|";

		// Column LAST NAME
		std::string	lastName = _contacts[i].getLastName();
		if (lastName.length() > 10)
			lastName = lastName.substr(0, 9) + ".";
		std::cout << std::setw(10) << lastName << "|";

		// Column NICKNAME
		std::string	nickname = _contacts[i].getNickname();
		if (nickname.length() > 10)
			nickname = nickname.substr(0, 9) + ".";
		std::cout << std::setw(10) << nickname << "|";

		std::cout << std::endl;
	}
	// 1. Déclarer la variable
	std::string	index_str;
	// 2. Demander à l'utilisateur
	std::cout << "Enter the index of contact to show: ";
	// 3. Lire l'entrée de l'utilisateur
	std::getline(std::cin, index_str);

	if (index_str.length() == 1 && index_str[0] >= '0' && index_str[0] <= '7')
	{
		int	index_num = index_str[0] - '0'; // Convertit le caractère '5' en entier 5

		if (index_num < this->_contact_count)
		{
			std::cout << "Prénom          : " << _contacts[index_num].getFirstName() << std::endl;
			std::cout << "Nom de famille  : " << _contacts[index_num].getLastName() << std::endl;
			std::cout << "Surnom          : " << _contacts[index_num].getNickname() << std::endl;
			std::cout << "Numéro de tel.  : " << _contacts[index_num].getPhoneNumber() << std::endl;
			std::cout << "Plus lourd secret : " << _contacts[index_num].getSecret() << std::endl;
		}
		else
			std::cout << "Erreur : Ce contact n'existe pas." << std::endl;
	}
	else
		std::cout << "Erreur : Index invalide." << std::endl;
}
