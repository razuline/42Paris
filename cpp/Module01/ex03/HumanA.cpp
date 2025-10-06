/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:30:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 20:12:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &weapon) :
		_name(name), _weapon(weapon) {
	// Tout le travail est fait dans la liste d'initialisation
}

HumanA::~HumanA(void) {
	// Cette classe ne gère pas de mémoire allouée dynamiquement
}

/* C'est la règle la plus importante à retenir sur les références
 * dans les classes : leur initialisation se fait toujours dans
 * la liste d'initialisation du constructeur. */

/* ------------------------------- FUNCTIONS -------------------------------- */

void	HumanA::attack(void) const {
	std::cout << this->_name << " attacks with their "
			<< this->_weapon.getType()
			<< std::endl;
}
