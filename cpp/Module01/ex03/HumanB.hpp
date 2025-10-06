/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 20:14:46 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 20:20:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMAN_B_HPP
# define HUMAN_B_HPP

# include "Weapon.hpp"
# include <string>

class HumanB
{
private:
	std::string	_name;
	Weapon		*_weapon; // Un pointeur peut être nul (NULL ou nullptr),
						  // ce qui représente parfaitement l'état "sans arme";
						  // Il n'a pas besoin d'être initialisé immédiatement
						  // à la construction.

public:
	// Le constructeur ne prend que le nom
	HumanB(std::string name);
	~HumanB(void);

	void	attack(void) const;
	void	setWeapon(Weapon &weapon);
};

#endif