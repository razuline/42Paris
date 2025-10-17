/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/17 16:51:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>

int	main(void)
{
	// --- Test 1 : Création et actions basiques ---
	std::cout << "--- CREATING ROBOTS ---" << std::endl;
	ScavTrap	scav("SC4V");
	FragTrap	frag("FR4G");
	std::cout << std::endl;

	// --- Test des valeurs initiales ---
	std::cout << "--- TESTING INITIAL VALUES ---" << std::endl;
	std::cout << "Initial HP [ FR4G ]: " << frag.getHitPoints()
				<< std::endl;      // Devrait afficher 100
	std::cout << "Initial Energy [ FR4G ]: " << frag.getEnergyPoints()
				<< std::endl;      // Devrait afficher 100
	std::cout << "Initial Damage [ FR4G ]: " << frag.getAttackDamage()
				<< std::endl;      // Devrait afficher 30

	// --- Actions de base ---
	std::cout << "\n--- BASIC ACTIONS TEST ---" << std::endl;
	frag.attack("Bandit");       // Il attaque
	frag.takeDamage(6);          // Il subit 6 points de dégâts
	frag.beRepaired(4);          // Il se répare de 4 points
	frag.highFivesGuys();
	std::cout << std::endl;

	 // --- Test 2 : Limites ---
	std::cout << "\n--- TESTING NO-LIFE SCENARIO ---" << std::endl;
	std::cout << "FragTrap HP before final damage: " << frag.getHitPoints()
			  << std::endl;
	frag.takeDamage(100);
	std::cout << "FragTrap HP after final damage: " << frag.getHitPoints()
			  << std::endl;

	// --- Test 3 : Copie et Assignation ---
	std::cout << "--- TESTING COPY AND ASSIGNMENT ---" << std::endl;
	FragTrap	frtrap("FR4G-E");
	frtrap.attack("Skag");
	std::cout << std::endl;

	std::cout << "--- Testing copy constructor ---" << std::endl;
	FragTrap	frag_copy(frtrap);
	frag_copy.attack("a big Skag");
	std::cout << std::endl;
	
	std::cout << "--- Testing assignment operator ---" << std::endl;
	FragTrap	frag_assign("TMP");
	frag_assign = frtrap;
	frag_assign.attack("a very big Skag");
	std::cout << std::endl;

	std::cout << "--- END OF MAIN ---" << std::endl;
	return 0;
}
