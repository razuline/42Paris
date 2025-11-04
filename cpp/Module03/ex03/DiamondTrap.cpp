/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:23:24 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/04 14:17:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

DiamondTrap::DiamondTrap(std::string name) :
		ClapTrap(name + "_clap_name"), // 1. Initialise la base virtuelle
		ScavTrap(name),                // 2. Appelle le constructeur de ScavTrap
		FragTrap(name),                // 3. Appelle le constructeur de FragTrap
		_name(name)             // 4. Initialise le nom spécifique à DiamondTrap
{
	// Assigner les bonnes valeurs aux attributs hérités
	this->_hit = FragTrap::_hit;
	this->_energy = ScavTrap::_energy;
	this->_damage = FragTrap::_damage;
	std::cout << "DiamondTrap " << this->_name << " is born!" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &copy) :
		ClapTrap(copy), // Appelle le constructeur de copie de ClapTrap
		ScavTrap(copy), // de ScavTrap
		FragTrap(copy), // de FragTrap
		_name(copy._name) // Initialise le membre propre à DiamondTrap
{
	std::cout << "DiamondTrap copy constructor called!" << std::endl;
}

DiamondTrap
&DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "DiamondTrap assignment operator called" << std::endl;
	if (this != &other) // Protection contre l'auto-assignation
	{
		// Appeler les opérateurs d'affectation des parents
		ClapTrap::operator=(other);
		// Pas besoin d'appeler ScavTrap et FragTrap car ils ne font
		// qu'appeler ClapTrap::operator= aussi.
		this->_name = other._name;
	}
	return *this;
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << "DiamondTrap " << this->_name << " is destroyed!" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
DiamondTrap::attack(const std::string &target)
{
	ScavTrap::attack(target);
}

void
DiamondTrap::takeDamage(unsigned int amount)
{
	FragTrap::takeDamage(amount);
}
void
DiamondTrap::beRepaired(unsigned int amount)
{
	ScavTrap::beRepaired(amount);
}

void
DiamondTrap::whoAmI(void)
{
	std::cout << "My DiamondTrap name is" << this->_name
				<< " and my ClapTrap name is " << ClapTrap::_name
				<< std::endl;
}
