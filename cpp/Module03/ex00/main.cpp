/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:41:49 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/17 15:35:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include <iostream>

int	main(void)
{
	// --- Scénario de base ---
	std::cout << "--- CREATING FIRST CLAPTRAP ---" << std::endl;
	ClapTrap	clap("CL4P-TP"); // Crée un ClapTrap nommé "CL4P-TP"

	std::cout << "\n--- BASIC ACTIONS TEST ---" << std::endl;
	clap.attack("Bandit");       // Il attaque
	clap.takeDamage(6);          // Il subit 6 points de dégâts
	clap.beRepaired(4);          // Il se répare de 4 points
	clap.takeDamage(3);          // Il subit encore 3 points de dégâts
	
	// --- Test des limites (plus assez de vie) ---
	std::cout << "\n--- TESTING NO-LIFE SCENARIO ---" << std::endl;
	clap.takeDamage(5);          // Il subit 5 points de dégâts (il n'a plus)
	clap.attack("another Bandit"); // Ne devrait pas pouvoir attaquer
	clap.beRepaired(10);         // Ne devrait pas pouvoir se réparer

	// --- Test de copie ---
	std::cout << "\n--- TESTING COPY AND ASSIGNMENT ---" << std::endl;
	ClapTrap	trap("TR4P"); // Crée un deuxième ClapTrap
	
	trap.attack("Skag");
	
	ClapTrap	trap_copy(trap); // Crée une copie de "TR4P"
	trap_copy.attack("a big Skag");
	
	ClapTrap	trap_assign("TMP");
	trap_assign = trap; // Assigne les valeurs de "TR4P" à "TMP"
	trap_assign.attack("a very big Skag");

	std::cout << "\n--- END OF MAIN ---" << std::endl;
	// Les destructeurs pour "clap", "trap", "trap_copy" et "trap_assign"
	// seront appelés automatiquement ici, dans l'ordre inverse de leur création.

	return 0;
}
