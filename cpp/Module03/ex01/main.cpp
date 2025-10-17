/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/17 15:39:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	// --- Test 1 : Création et actions basiques ---
	std::cout << "--- CREATING ROBOTS ---" << std::endl;
	FlagTrap	scav("SC4V");
	std::cout << std::endl;

	// --- Test des valeurs initiales ---
	std::cout << "--- TESTING INITIAL VALUES ---" << std::endl;
	std::cout << "Initial HP: " << scav.getHitPoints()
				<< std::endl;      // Devrait afficher 100
	std::cout << "Initial Energy: " << scav.getEnergyPoints()
				<< std::endl;      // Devrait afficher 50
	std::cout << "Initial Damage: " << scav.getAttackDamage()
				<< std::endl;      // Devrait afficher 20

	std::cout << "\n--- BASIC ACTIONS TEST ---" << std::endl;
	scav.attack("Bandit");       // Il attaque
	scav.takeDamage(6);          // Il subit 6 points de dégâts
	scav.beRepaired(4);          // Il se répare de 4 points
	scav.guardGate();

	 // --- Test 2 : Limites ---
	std::cout << "\n--- TESTING NO-LIFE SCENARIO ---" << std::endl;
	scav.takeDamage(5);          // Il subit 5 points de dégâts (il n'a plus)
	scav.attack("another Bandit"); // Ne devrait pas pouvoir attaquer
	scav.beRepaired(10);         // Ne devrait pas pouvoir se réparer

	// --- Test 3 : Copie ---
	std::cout << "\n--- TESTING COPY AND ASSIGNMENT ---" << std::endl;
	FlagTrap sctrap("SC4V-E");
	
	sctrap.attack("Skag");
	
	FlagTrap scav_copy(scav);
	scav_copy.attack("a big Skag");
	
	FlagTrap scav_assign("TMP");
	scav_assign = scav;
	scav_assign.attack("a very big Skag");

	std::cout << "\n--- END OF MAIN ---" << std::endl;
	// Les destructeurs pour "clap", "trap", "trap_copy" et "trap_assign"
	// seront appelés automatiquement ici, dans l'ordre inverse de leur création.

	return 0;
}
