/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:54:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/15 14:21:58 by erazumov         ###   ########.fr       */
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

ClapTrap::ClapTrap(const ClapTrap &copy)
{
	*this = copy;
	std::cout << "ClapTrap " << this->_name << " has been cloned!"
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

/* ------------------------------- FUNCTIONS -------------------------------- */

void
ClapTrap::attack(const std::string &target)
{
	if (_hit > 0 && _energy > 0)
		_energy--;
	std::cout << "ClapTrap " << this->_name << "attacks " this->_target << ", causing" <damage> points of damage!
}

void
ClapTrap::takeDamage(unsigned int amount)
{
	
}

void
ClapTrap::beRepaired(unsigned int amount)
{
	
}
