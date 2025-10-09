/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:22:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 20:36:14 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL) {
	// Initialiser le pointeur à NULL pour indiquer "pas d'arme"
}

HumanB::~HumanB(void) {
	// Cette classe ne gère pas de mémoire allouée dynamiquement
}

/* -------------------------------- SETTERS --------------------------------- */

void	HumanB::setWeapon(Weapon &weapon) {
	// Stocker l'ADRESSE de l'arme dans le pointeur
	this->_weapon = &weapon;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void	HumanB::attack(void) const {
	// Vérifie d'abord si une arme est équipée (si le pointeur n'est pas NULL)
	if (this->_weapon) {
		std::cout << this->_name << " attacks with their "
				<< this->_weapon->getType() << std::endl;
	}
	else {
		std::cout << this->_name << " attacks with their bare hands"
				<< std::endl;
	}
}
