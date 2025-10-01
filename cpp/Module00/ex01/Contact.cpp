/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:46:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/30 18:12:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Contact.hpp"

Contact::Contact(void) {
	// Rien à faire ici, le constructeur est vide
}

Contact::~Contact(void) {
	// Rien à nettoyer, le destructeur est vide
}

bool	Contact::_onlyAlpha(const std::string& input) {
	for (size_t i = 0; i < input.length(); i++) {
		if (!std::isalpha(input[i]))
			return false;
	}
	return true;
}

bool	Contact::_onlyDigits(const std::string& input) {
	for (size_t i = 0; i < input.length(); i++) {
		if (!std::isdigit(input[i]))
			return false;
	}
	return true;
}

/* -------------------------------- SETTERS --------------------------------- */

bool	Contact::setFirstname(const std::string& str) {
	if (!str.empty() && this->_onlyAlpha(str) == true) {
	this->_firstname = str;
	return true;
	}
	return false;
}

bool	Contact::setLastname(const std::string& str) {
	if (!str.empty() && this->_onlyAlpha(str) == true) {
	this->_lastname = str;
	return true;
	}
	return false;
}

bool	Contact::setNickname(const std::string& str) {
	if (!str.empty() && this->_onlyAlpha(str) == true) {
	this->_nickname = str;
	return true;
	}
	return false;
}

bool	Contact::setNumber(const std::string& str) {
	if (!str.empty() && this->_onlyDigits(str) == true) {
	this->_number = str;
	return true;
	}
	return false;
}

bool	Contact::setSecret(const std::string& str) {
	if (!str.empty() && this->_onlyAlpha(str) == true) {
	this->_secret = str;
	return true;
	}
	return false;
}

/* -------------------------------- GETTERS --------------------------------- */

std::string	Contact::getFirstname(void) const {
	return this->_firstname;
}

std::string	Contact::getLastname(void) const {
	return this->_lastname;
}

std::string	Contact::getNickname(void) const {
	return this->_nickname;
}

std::string	Contact::getNumber(void) const {
	return this->_number;
}

std::string	Contact::getSecret(void) const {
	return this->_secret;
}
