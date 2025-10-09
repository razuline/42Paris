/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:32:37 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/05 18:07:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Zombie.hpp"

/*
 * Créer un zombie sur la heap (le tas), ce qui lui permet de "vivre"
 * même après la fin de la fonction.
 */
Zombie	*newZombie(std::string name) {
	// Créer un nouveau zombie et stocke son adresse dans le pointeur newZ
	Zombie	*newZ = new Zombie(name);
	// Retourner le pointeur pour qu'on puisse accéder au zombie
	return newZ;
}

/* L'opérateur new va allouer de la mémoire et donner en retour l'adresse
 * du nouveau zombie. */
