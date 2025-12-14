/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:42:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 14:10:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include <iostream>
# include <string>

# include "AMateria.hpp"
# include "ICharacter.hpp"

class Ice : public AMateria
{
public:
	Ice();
	Ice(const Ice &copy);
	Ice &operator=(const Ice &other);
	virtual ~Ice();

	// --- Member Functions ---
	virtual			AMateria *clone() const;
	virtual void	use(ICharacter& target);
};

#endif