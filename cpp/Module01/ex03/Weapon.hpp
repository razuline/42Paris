/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:09:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 19:25:42 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <iostream>
# include <string>

class Weapon
{
private:
	std::string	_type;

public:
	// Constructeur qui prend le type de l'arme
	Weapon(std::string type);
	~Weapon(void);

	// Retourner une référence constante pour lire le type
	void				setType(const std::string &newType);

	// Modifier le type de l'arme
	const std::string	&getType(void) const;
};

#endif