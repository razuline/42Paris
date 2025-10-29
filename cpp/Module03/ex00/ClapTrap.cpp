/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/29 14:29:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

ClapTrap::ClapTrap(std::string name) :
	_name(name), _hit(10), _energy(10), _damage(0)
{
	std::cout << "ClapTrap " << this->_name << " is born!"
				<< std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &copy) :
	_name(copy._name), _hit(copy._hit), _energy(copy._energy),
	_damage(copy._damage)
{
	std::cout << "ClapTrap " << this->_name << " copy constructor called!"
				<< std::endl;
}

ClapTrap
&ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "ClapTrap assignment operator called." << std::endl;
	if (this != &other) // Protection contre l'auto-assignation
	{
		this->_name = other._name;
		this->_hit = other._hit;
		this->_energy = other._energy;
		this->_damage = other._damage;
	}
	return *this;
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap " << this->_name << " is destroyed!"
				<< std::endl;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

// Logique d'attaque : vérifie l'énergie/vie, dépense 1 énergie,
// affiche un message.
void
ClapTrap::attack(const std::string &target)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		this->_energy--;
		std::cout << "ClapTrap " << this->_name << " attacks " << target
					<< ", causing " << this->_damage << " points of damage!"
					<< std::endl;
	}
	else
	{
		std::cout << "ClapTrap " << this->_name << " can't attack, not enough "
					"energy or hit points." << std::endl;
	}
}

// Réduit les points de vie et affiche le résultat.
void
ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hit > amount)
		this->_hit -= amount;
	else
		this->_hit = 0; // Pour éviter des points de vie négatifs
	std::cout << "ClapTrap " << this->_name << " takes "
				<< amount << " points of damage!" << std::endl;
}

// Logique de réparation : vérifie l'énergie/vie, dépense 1 énergie,
// regagne de la vie.
void
ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		this->_energy--;
		this->_hit += amount;
		std::cout << "ClapTrap " << this->_name << " repairs itself, gaining "
					<< amount << " hit points back!"
					<< std::endl;
	}
	else
	{
		std::cout << "ClapTrap " << this->_name << " can't repair, not enough "
					"energy or hit points." << std::endl;
	}
}
