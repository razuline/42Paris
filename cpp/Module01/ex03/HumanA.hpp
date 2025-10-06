/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:20:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 20:17:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_A_HPP
# define HUMAN_A_HPP

# include "Weapon.hpp"
# include <string>

class HumanA
{
private:
	std::string	_name;
	Weapon		&_weapon; // Une référence ne peut pas être nulle, ce qui
						  // garantit que HumanA a toujours une arme;
						  // Doit être initialisée à la construction.

public:
	// Le constructeur prend le nom et une référence vers l'arme
	HumanA(std::string name, Weapon &weapon);
	~HumanA(void);

	void	attack(void) const;
};

#endif