/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:17:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/11 15:50:18 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void) {
	// Créer une instance (un objet) de la classe Harl.
	Harl	harl;

	// Afficher des titres pour que la sortie soit claire.
	std::cout << "[ DEBUG LEVEL ]" << std::endl;
	// Appeller la méthode 'complain' avec le niveau "DEBUG".
	harl.complain("DEBUG");
	std::cout << std::endl;

	std::cout << "[ INFO LEVEL ]" << std::endl;
	harl.complain("INFO");
	std::cout << std::endl;

	std::cout << "[ WARNING LEVEL ]" << std::endl;
	harl.complain("WARNING");
	std::cout << std::endl;

	std::cout << "[ ERROR LEVEL ]" << std::endl;
	harl.complain("ERROR");
	std::cout << std::endl;

	std::cout << "[ INVALID LEVEL ]" << std::endl;
	harl.complain("RANDOM");

	return 0;
}
