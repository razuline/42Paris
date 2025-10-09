/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:26:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 19:18:57 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) { // Liste d'initialisation
	// Rien à faire ici, le constructeur est vide
}

Weapon::~Weapon(void) {
	// Comme ka classe ne gère pas de mémoire allouée dynamiquement (avec new),
	// le destructeur n'a rien de spécial à faire
}

/* -------------------------------- SETTERS --------------------------------- */

void	Weapon::setType(const std::string &newType) {
	this->_type = newType;
}

/* -------------------------------- GETTERS --------------------------------- */

const std::string	&Weapon::getType(void) const {
	return Weapon::_type;
}
