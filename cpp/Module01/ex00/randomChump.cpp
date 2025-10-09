/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomChump.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 17:33:09 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/05 18:19:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Zombie.hpp"

/*
 * Créer un zombie sur la stack (la pile). Sa durée de vie sera limitée
 * à cette fonction uniquement.
 */
void	randomChump(std::string name) {
	// Créer une instance de Zombie nommée myZombie
	Zombie	myZombie(name);
	// Demander à CETTE instance précise d'exécuter sa méthode announce
	myZombie.announce();
}
