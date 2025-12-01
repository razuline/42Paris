/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:24:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 14:36:23 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>

class ICharacter; // Forward declaration

class AMateria
{
protected:
	std::string	_type;

public:
	AMateria(std::string const &type);
	AMateria(const AMateria &copy);
	AMateria &operator=(const AMateria &other);
	virtual ~AMateria();

	// --- Getters ---
	std::string const	&getType() const; // Returns the materia type

	// --- Member Functions ---
	virtual			AMateria *clone() const = 0; // Pure virtual->abstract class
	virtual void	use(ICharacter& target);
};

#endif