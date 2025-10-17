/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:03:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/17 16:36:16 by erazumov         ###   ########.fr       */
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
	std::cout << "FragTrap " << this->_name << " has been cloned!" << std::endl;
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

// Logique d'attaque : vérifie l'énergie/vie, dépense 1 énergie,
// affiche un message.
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
	if (this->_hit > 0)
	{
		this->_hit -= amount;
		if (this->_hit < 0)
			this->_hit = 0;
		std::cout << "FragTrap " << this->_name << " takes "
				  << amount << " points of damage!" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->_name << " is already destroyed."
				  << std::endl;
	}
}

// Logique de réparation : vérifie l'énergie/vie, dépense 1 énergie,
// regagne de la vie.
void
FragTrap::beRepaired(unsigned int amount)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		_energy--;
		this->_hit += amount;
		std::cout << "FragTrap " << this->_name << " repairs itself, gaining "
					<< amount << " hit points back!" << std::endl;
	}
	else
	{
		std::cout << "FragTrap " << this->_name << " can't repair, not enough "
					"energy or hit points." << std::endl;
	}
}

void
FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << this->_name 
			  << " says: 'High five, guys! Anyone?' 🙌" << std::endl;
}
