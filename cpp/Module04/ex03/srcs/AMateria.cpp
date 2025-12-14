/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 13:29:25 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 14:37:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "ICharacter.hpp"

AMateria::AMateria(std::string const &type) : _type(type)
{
	// std::cout << "AMateria constructor" << std::endl;
}

AMateria::AMateria(const AMateria& copy) : _type(copy._type)
{
	// std::cout << "AMateria copy constructor" << std::endl;
}

AMateria
&AMateria::operator=(const AMateria &other)
{
	if (this != &other)
		// Subject says copying type doesn't really make sense,
			// but we keep interface consistent
		this->_type = other._type;
	return *this;
}

AMateria::~AMateria()
{
	// std::cout << "AMateria destructor" << std::endl;
}

std::string const
&AMateria::getType(void) const
{
	return this->_type;
}

void
AMateria::use(ICharacter& target)
{
	(void)target; // Default implementation does nothing
}
