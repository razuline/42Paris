/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 15:23:57 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/29 16:07:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMOND_TRAP_HPP
# define DIAMOND_TRAP_HPP

# include <iostream>
# include <string>
# include "ClapTrap.hpp"
# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
	std::string		_name;

public:
	DiamondTrap(std::string name);
	DiamondTrap(const DiamondTrap &copy);
	DiamondTrap &operator=(const DiamondTrap &other);
	~DiamondTrap(void);
};

#endif