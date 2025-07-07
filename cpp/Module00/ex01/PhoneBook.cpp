/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:24:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/07 13:37:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "PhoneBook.hpp"

void	PhoneBook::addContact()
{
	std::string firstName, lastName, nickname, phoneNumber, secret;

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
}


