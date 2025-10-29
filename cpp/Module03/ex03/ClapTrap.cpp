/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/29 15:05:28 by erazumov         ###   ########.fr       */
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

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap " << this->_name << " is destroyed!"
				<< std::endl;
}

/* --------------------------- SETTERS & GETTERS ---------------------------- */

unsigned int
ClapTrap::getHitPoints(void) const
{
	return this->_hit;
}

unsigned int
ClapTrap::getEnergyPoints(void) const
{
	return this->_energy;
}

unsigned int
ClapTrap::getAttackDamage(void) const
{
	return this->_damage;
}

/* ------------------------------- FUNCTIONS -------------------------------- */

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

void
ClapTrap::takeDamage(unsigned int amount)
{
	if (this->_hit == 0)
	{
		// Pas besoin de message ici, car la classe est "silencieuse"
		return; 
	}
	
	if (amount >= this->_hit)
		this->_hit = 0;
	else
		this->_hit -= amount;
}

void
ClapTrap::beRepaired(unsigned int amount)
{
	if (this->_hit > 0 && this->_energy > 0)
	{
		this->_energy--;
		this->_hit += amount;
	}
}
