/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:34:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 16:02:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie*	zombieHorde(int N, std::string name) {
	// Allocation
	Zombie	*zHorde = new Zombie[N];

	// Boucle pour nommer chaque zombie
	for (int i = 0; i < N; i++) {
		zHorde[i].setName(name);
	}

	// Retourner le pointeur vers le début de la horde
	return zHorde;
}
