/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:43 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/07 16:17:11 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <vector>
# include <algorithm>

class bigint
{
private:
	std::vector<int>	_digits; // Digits are stored in reverse order: 1337 -> {7, 3, 3, 1}

	/* --- Private Helper Methods --- */
	void	_removeLeadingZeros(); // Remove leading zeros (e.g., 0042 -> 42)
	int		_toInt() const; // Convert a small bigint to int (used for shifting logic)

public:
	/* --- Orthodox Canonical Form --- */
	bigint();
	bigint(unsigned long long n);
	bigint(const bigint &copy);
	bigint	&operator=(const bigint &other);
	~bigint();

	/* --- Arithmetic Operators --- */
	bigint	operator+(const bigint &other) const;
	bigint	&operator+=(const bigint &other);

	/* --- Increment --- */
	bigint	&operator++();   // Prefix ++b
	bigint	operator++(int); // Postfix b++

	// Digitshift (Base 10 shifting)
	bigint	operator<<(unsigned int n) const;
	bigint	&operator<<=(unsigned int n);
	bigint	operator>>(unsigned int n) const;
	bigint	&operator>>=(unsigned int n);

	// Shift overloads to handle (d >>= (const bigint)2) from main
	bigint	operator>>(const bigint &other) const;
	bigint	&operator>>=(const bigint &other);

	/* --- Comparison --- */
	bool	operator<(const bigint &other) const;
	bool	operator<=(const bigint &other) const;
	bool	operator>(const bigint &other) const;
	bool	operator>=(const bigint &other) const;
	bool	operator==(const bigint &other) const;
	bool	operator!=(const bigint &other) const;

	/* --- Core Methods --- */
	void	print(std::ostream &os) const;
};

/* --- Output Stream --- */
std::ostream
&operator<<(std::ostream &os, const bigint &obj);

#endif