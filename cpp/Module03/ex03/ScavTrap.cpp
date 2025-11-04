/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:26:13 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/04 14:17:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	this->_hit = 100;
	this->_energy = 50;
	this->_damage = 20;
	std::cout << "ScavTrap " << this->_name << " is born!" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy)
{
	std::cout << "A ScavTrap has been created by copy!" << std::endl;
}

ScavTrap
&ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap assignment operator called" << std::endl;
	if (this != &other) // Protection contre l'auto-assignation
	{
		ClapTrap::operator=(other);
		// Membres propres à ScavTrap s'il y en a
	}
	return *this;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap " << this->_name << " is destroyed!" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
ScavTrap::attack(const std::string &target)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		this->_energy--;
		std::cout << "ScavTrap " << this->_name << " attacks " << target
					<< ", causing " << this->_damage << " points of damage!"
					<< std::endl;
	}
	else
	{
		std::cout << "ScavTrap " << this->_name << " can't attack, not enough "
					"energy or hit points." << std::endl;
	}
}

void
ScavTrap::takeDamage(unsigned int amount)
{
	std::cout << "ScavTrap " << this->_name << " takes "
				<< amount << " points of damage!" << std::endl;

	// Appeler à la méthode de la classe mère
	ClapTrap::takeDamage(amount);
}

void
ScavTrap::beRepaired(unsigned int amount)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		std::cout << "ScavTrap " << this->_name << " initiates repair protocol!"
					<< std::endl;
		ClapTrap::beRepaired(amount);
	}
	else
	{
		std::cout << "ScavTrap " << this->_name
					<< " repair systems are offline." << std::endl;
	}
}

// Afficher un message indiquant que le ScavTrap est passé
// en mode "Gate keeper".
void
ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode!"
				<< std::endl;
}
