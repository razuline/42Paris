/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:33:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 15:09:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Zombie.hpp"

int	main(void) {
	std::cout << "--- Création d'un zombie sur la Heap ---" << std::endl;
	// On appelle newZombie ET on stocke le pointeur retourné dans heapZombie
	Zombie *heapZombie = newZombie("Foo");
	// Maintenant, heapZombie contient bien l'adresse du zombie "Foo"
	heapZombie->announce();

	std::cout << "--- Création d'un zombie sur la Stack ---" << std::endl;
	randomChump("Ed");

	std::cout << "--- Destruction manuelle du zombie de la Heap ---"
			<< std::endl;
	// On peut maintenant supprimer le zombie en toute sécurité
	delete heapZombie;

	return 0;
}
