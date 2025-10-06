/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 15:26:23 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/06 15:35:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HORDE_HPP
# define ZOMBIE_HORDE_HPP

# include <iostream>
# include <string>

class Zombie
{
private:
	std::string	_name;

public:
	// Le constructeur par défaut
	Zombie(void);
	// Le constructeur de ex00
	Zombie(std::string name);
	// Le destructeur
	~Zombie(void);

	// La méthode pour parler
	void	announce(void);
	// La méthode pour donner un nom après la création
	void	setName(std::string name);
};

Zombie*	zombieHorde(int N, std::string name);

#endif