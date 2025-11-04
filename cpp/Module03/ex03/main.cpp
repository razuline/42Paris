/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/04 14:18:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	 // --- TEST 1 : CONSTRUCTION ET DESTRUCTION ---
	std::cout << "--- Testing Construction ---" << std::endl;
	DiamondTrap diamond("DI4M-TP");
	std::cout << std::endl;
	// Afficher la chaîne de construction :
	// ClapTrap, ScavTrap, FragTrap, puis DiamondTrap.

	// --- TEST 2 : VÉRIFICATION DES STATS ---
	std::cout << "--- Testing Stats ---" << std::endl;
	// Afficher les Hit Points, Energy Points et Attack Damage.
	// Vérifier que les valeurs sont correctes :
	// HP: 100 (de FragTrap)
	// Energy: 50 (de ScavTrap)
	// Damage: 30 (de FragTrap)
	std::cout << "HP: " << diamond.getHitPoints() << std::endl;
	// ... faire de même pour l'énergie et les dégâts.
	std::cout << std::endl;

	// --- TEST 3 : TEST DES FONCTIONS ---
	std::cout << "--- Testing Functions ---" << std::endl;
	// Attaquer DiamondTrap.
	// Le message doit être celui de ScavTrap.
	diamond.attack("un petit méchant");

	// Faire-le se réparer.
	diamond.beRepaired(10);

	// Faire-lui prendre des dégâts.
	diamond.takeDamage(20);

	// Les deux noms doivent s'afficher.
	diamond.whoAmI();
	std::cout << std::endl;

	// Teste les fonctions des classes parentes.
	// DiamondTrap doit pouvoir utiliser guardGate() et highFivesGuys().
	diamond.guardGate();
	diamond.highFivesGuys();
	std::cout << std::endl;


	// --- TEST 4 : DESTRUCTION ---
	std::cout << "--- Testing Destruction ---" << std::endl;
	// L'ordre de destruction:
	// DiamondTrap, FragTrap, ScavTrap, puis ClapTrap.

	return 0;
}
