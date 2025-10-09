/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:10:14 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/09 14:24:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

# include <cmath>
# include <iostream>
# include <string>

class Fixed
{
private:
	int					_fixed;
	static const long	_bits = 8;

public:
	Fixed(void);
	Fixed(const int n);
	Fixed(const float f);
	Fixed(const Fixed &copy);
	~Fixed(void);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);

	int		toInt(void) const;
	float	toFloat(void) const;

	// 1. Opérateurs de comparaison
	bool	operator>(const Fixed &other) const;
	bool	operator<(const Fixed &other) const;
	bool	operator>=(const Fixed &other) const;
	bool	operator<=(const Fixed &other) const;
	bool	operator==(const Fixed &other) const;
	bool	operator!=(const Fixed &other) const;

	// 2. Opérateurs arithmétiques
	Fixed	operator+(const Fixed &other) const;
	Fixed	operator-(const Fixed &other) const;
	Fixed	operator*(const Fixed &other) const;
	Fixed	operator/(const Fixed &other) const;

	// 3. Opérateurs d'incrémentation / décrémentation
	Fixed	&operator++(void); // Pré-incrémentation (++a)
	Fixed	operator++(int);   // Post-incrémentation (a++)
	Fixed	&operator--(void); // Pré-décrémentation (--a)
	Fixed	operator--(int);   // Post-décrémentation (a--)

	// 4. Fonctions statiques min / max
	static Fixed		&min(Fixed &a, Fixed &b);
	static const Fixed	&min(const Fixed &a, const Fixed &b);
	static Fixed		&max(Fixed &a, Fixed &b);
	static const Fixed	&max(const Fixed &a, const Fixed &b);

	// Opérateur d'affectation est utilisé quand on copie un objet
	// dans un autre qui existe déjà
	Fixed	&operator=(const Fixed &other);
};

std::ostream &operator<<(std::ostream &out, const Fixed &value);

#endif