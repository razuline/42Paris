/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:04:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/07 20:23:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void) {
	
}

Harl::~Harl(void) {
	
}

/* ------------------------------- FUNCTIONS -------------------------------- */

void	Harl::debug(void) {
	std::cout << "I love having extra bacon for my "
					"7XL-double-cheese-triple-pickle-specialketchup burger. "
					"I really do!"
					<< std::endl;
}

void	Harl::info(void) {
	std::cout << "I cannot believe adding extra bacon costs more money. "
					"You didn’t put enough bacon in my burger! "
					"If you did, I wouldn’t be asking for more!"
					<< std::endl;
}

void	Harl::warning(void) {
	std::cout << "I think I deserve to have some extra bacon for free. "
					"I’ve been coming for years, "
					"whereas you started working here just last month."
					<< std::endl;
}

void	Harl::error(void) {
	std::cout << "This is unacceptable! I want to speak to the manager now."
					<< std::endl;
}

void	Harl::complain(std::string level) {
	// Type personnalisé pour simplifier la syntaxe des ptrs de fonc membre.
	typedef void (Harl::*HarlMemberFunction)(void);

	// Tableau des noms des niveaux.
	std::string	levels[] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};

	// Tableau des pointeurs vers les fonctions membres correspondantes.
	HarlMemberFunction	functions[] = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	// Boucle pour trouver le bon niveau.
	for (int i = 0; i < 4; i++) {
		// Si le niveau entré correspond à un niveau connu,...
		if (level == levels[i]) {
			// ...appeller la fonc correspondante de la syntaxe spéciale.
			(this->*functions[i])();
			return; // Trouvé, on peut quitter la fonction.
		}
	}
}
