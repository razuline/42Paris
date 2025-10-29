/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:23:24 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/29 16:22:20 by erazumov         ###   ########.fr       */
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
	_name(copy._name), FragTrap::_hit(copy._hit), _energy(copy._energy),
	_damage(copy._damage)
{
	std::cout << "ClapTrap " << this->_name << " copy constructor called!"
				<< std::endl;
}

DiamondTrap
&DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "ClapTrap assignment operator called" << std::endl;
	if (this != &other) // Protection contre l'auto-assignation
	{
		this->_name = other._name;
		this->_hit = other._hit;
		this->_energy = other._energy;
		this->_damage = other._damage;
	}
	return *this;
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << "ClapTrap " << this->_name << " is destroyed!"
				<< std::endl;
}
