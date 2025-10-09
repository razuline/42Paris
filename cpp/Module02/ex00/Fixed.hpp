/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:11:01 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/08 14:09:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>
# include <string>

class Fixed
{
private:
	int					_fixed;
	static const int	_bits = 8;

public:
	Fixed(void);
	Fixed(const Fixed &copy);
	~Fixed(void);

	// Opérateur d'affectation est utilisé quand on copie un objet
	// dans un autre qui existe déjà
	Fixed	&operator=(const Fixed &other);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);
};

#endif