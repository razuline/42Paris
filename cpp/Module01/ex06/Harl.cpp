/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:04:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/07 19:55:08 by erazumov         ###   ########.fr       */
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
