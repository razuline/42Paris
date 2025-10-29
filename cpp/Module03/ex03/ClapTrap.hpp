/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:33:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/17 12:00:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

# include <iostream>
# include <string>

class ClapTrap
{
protected:
	std::string		_name;
	unsigned int	_hit;
	unsigned int	_energy;
	unsigned int	_damage;

public:
	ClapTrap(std::string name); // Constructeur
	ClapTrap(const ClapTrap &copy); // Constructeur de copie
	ClapTrap &operator=(const ClapTrap &other); // Opérateur d'assignation
	~ClapTrap(void); // Destructeur

	// --- Getters ---
	unsigned int	getHitPoints(void) const;
	unsigned int	getEnergyPoints(void) const;
	unsigned int	getAttackDamage(void) const;

	// --- Fonctions membres ---
	void	attack(const std::string &target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
};

#endif