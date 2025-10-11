/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:05:57 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/11 15:46:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

std::string	levels[] = {
	"DEBUG",
	"INFO",
	"WARNING",
	"ERROR"
};

int	main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Usage: ./harlFilter <level>" << std::endl;
		return 1;
	}

	Harl		harl;
	std::string	lvl = av[1];
	int			lvlIdx = -1;

	for (int i = 0; i < 4; i++) {
		// Si l'argument correspond à un niveau connu...
		if (lvl == levels[i]) {
			// ...stocker son index et on sort de la boucle.
			lvlIdx = i;
			break;
		}
	}
	switch (lvlIdx)
	{
	case 0: // Cas pour "DEBUG"
		std::cout << "[ DEBUG ]" << std::endl;
		harl.complain("DEBUG");
		// Pas de break, on continue au cas suivant
	case 1: // Cas pour "INFO"
		std::cout << "[ INFO ]" << std::endl;
		harl.complain("INFO");
		// Pas de break, on continue au cas suivant
	case 2: // Cas pour "WARNING"
		std::cout << "[ WARNING ]" << std::endl;
		harl.complain("WARNING");
		// Pas de break, on continue au cas suivant
	case 3: // Cas pour "ERROR"
		std::cout << "[ ERROR ]" << std::endl;
		harl.complain("ERROR");
		break;
	default: // S'exécute si lvlIdx est resté à -1
		std::cout << "[ Probably complaining about insignificant problems ]"
					<< std::endl;
		break;
	}
	return 0;
}
