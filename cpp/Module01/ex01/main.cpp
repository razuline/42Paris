/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:46:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 16:10:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void) {
	// Choisir un nombre de zombies
	int	N = 5;
	// Appeler la fonction ET stocker le pointeur
	Zombie	*horde = zombieHorde(N, "Jack");

	// Vérifier la horde en faisant parler chaque zombie
	for (int i = 0; i < N; i++) {
		horde[i].announce();
	}
	// Détruire TOUTE la horde avec delete[]
	delete[] horde;

	return 0;
}
