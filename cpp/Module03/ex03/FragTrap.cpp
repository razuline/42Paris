/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:03:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/29 15:11:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	this->_hit = 100;
	this->_energy = 100;
	this->_damage = 30;
	std::cout << "FragTrap " << this->_name << " is born!" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy)
{
	std::cout << "A FragTrap has been created by copy!" << std::endl;
}

FragTrap
&FragTrap::operator=(const FragTrap &other)
{
	std::cout << "FragTrap assignment operator called" << std::endl;
	if (this != &other) // Protection contre l'auto-assignation
	{
		ClapTrap::operator=(other);
		// Membres propres à FragTrap s'il y en a
	}
	return *this;
}

FragTrap::~FragTrap(void)
{
	std::cout << "FragTrap " << this->_name << " is destroyed!" << std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void
FragTrap::attack(const std::string &target)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		this->_energy--;
		std::cout << "FragTrap " << this->_name << " attacks " << target
					<< ", causing " << this->_damage << " points of damage!"
					<< std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->_name << " can't attack, not enough "
					"energy or hit points." << std::endl;
	}
}

void
FragTrap::takeDamage(unsigned int amount)
{
	// Si on veut un message avant l'action
	if (this->_hit == 0)
	{
		std::cout << "FragTrap " << this->_name
					<< " is already a pile of scraps!" << std::endl;
		return;
	}
	
	// Appeller la logique de la classe mère
	ClapTrap::takeDamage(amount);

	// Afficher le résultat
	std::cout << "FragTrap " << this->_name << " takes " << amount
				<< " points of damage!" << std::endl;
	if (this->_hit == 0)
	{
		std::cout << "FragTrap " << this->_name
				<< " has been utterly destroyed!" << std::endl;
	}
}

void
FragTrap::beRepaired(unsigned int amount)
{
	// La classe fille gère l'affichage et les conditions spécifiques.
	if (this->_hit > 0 && this->_energy > 0)
	{
		std::cout << "FragTrap " << this->_name << " starts nanobot repairs!"
					<< std::endl;
		// Appeller la logique de la classe mère pour faire le vrai travail.
		ClapTrap::beRepaired(amount);
	}
	else
	{
		std::cout << "FragTrap " << this->_name
					<< " can't repair, it's a lost cause." << std::endl;
	}
}

void
FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name 
			  << " says: 'High five, guys! Anyone?' 🙌" << std::endl;
}
