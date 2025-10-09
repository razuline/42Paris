/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:28:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 20:42:15 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void) {
	// Rien à faire ici, le constructeur est vide
}

Zombie::Zombie(std::string name) {
	_name = name;
}

Zombie::~Zombie(void) {
	std::cout << _name << "-zombie was destroyed!" << std::endl;
}

/* -------------------------------- SETTERS --------------------------------- */

void	Zombie::setName(std::string name) {
	this->_name = name;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void	Zombie::announce(void) {
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
