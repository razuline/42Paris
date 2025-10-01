/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:46:12 by erazumov          #+#    #+#             */
/*   Updated: 2025/09/30 18:08:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <cctype>
# include <string>

class Contact
{
private:
	// Stocke les données, pas des adresses
	std::string	_firstname;
	std::string	_lastname;
	std::string	_nickname;
	std::string	_number;
	std::string	_secret;

	bool		_onlyAlpha(const std::string& input);
	bool		_onlyDigits(const std::string& input);

public:
	Contact(void);
	~Contact(void);

	// Setters (Prendre des références constantes pour être efficaces)
	bool		setFirstname(const std::string& str);
	bool		setLastname(const std::string& str);
	bool		setNickname(const std::string& str);
	bool		setNumber(const std::string& str);
	bool		setSecret(const std::string& str);

	// Getters (Retourner une copie de la donnée)
	std::string	getFirstname(void) const;
	std::string	getLastname(void) const;
	std::string	getNickname(void) const;
	std::string	getNumber(void) const;
	std::string	getSecret(void) const;
};

#endif