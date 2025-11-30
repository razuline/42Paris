/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:24:22 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/30 13:28:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <iostream>
# include <string>

class ICharacter;

class AMateria
{
protected:
	std::string	_type;

public:
	AMateria(std::string const &type);
	AMateria(const AMateria &copy);
	AMateria &operator=(const AMateria &other);
	virtual ~AMateria(void);

	// --- Getters ---
	std::string const	&getType(void) const; // Returns the materia type

	// --- Member Functions ---
	virtual			AMateria *clone(void) const = 0; // Pure virtual = Abstraite
	virtual void	use(ICharacter& target);
};

#endif