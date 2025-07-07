/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 12:10:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/07 16:18:42 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

void	Contact::setFirstName(std::string str)
{
	this->_first_name = str;
}
void	Contact::setLastName(std::string str)
{
	this->_last_name = str;
}
void	Contact::setNickname(std::string str)
{
	this->_nickname = str;
}

void	Contact::setPhoneNumber(std::string str)
{
	this->_phone_number = str;
}
void	Contact::setSecret(std::string str)
{
	this->_darkest_secret = str;
}

std::string	Contact::getFirstName(void) const
{
	return (this->_first_name);
}

std::string	Contact::getLastName(void) const
{
	return (this->_last_name);
}

std::string	Contact::getNickname(void) const
{
	return (this->_nickname);
}

std::string	Contact::getPhoneNumber(void) const
{
	return (this->_phone_number);
}

std::string	Contact::getSecret(void) const
{
	return (this->_darkest_secret);
}
