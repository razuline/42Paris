/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:43 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/10 15:12:45 by erazumov         ###   ########.fr       */
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
	int		_toInt() const; // Convert a small bigint to int (used for shifting logic)
	void	_removeLeadingZeros(); // Remove leading zeros (e.g., 0042 -> 42)

public:
	/* --- Orthodox Canonical Form --- */
	bigint();                                 // Default
	bigint(unsigned long long n);             // Int conversion
	bigint(const bigint &copy);               // Copy
	bigint	&operator=(const bigint &other);  // Assignment
	~bigint();                                // Destructor

	// 1. Arithmetic Operators
	bigint	&operator+=(const bigint &other);
	bigint	operator+(const bigint &other) const;

	// 2. Increment Operators
	bigint	&operator++();    // Prefix (++i)
	bigint	operator++(int);  // Postfix (i++)

	// 3. Digitshift Operators

	// Left Shifts
	bigint	&operator<<=(unsigned int n);
	bigint	operator<<(unsigned int n) const;

	// Right Shifts
	bigint	&operator>>=(unsigned int n);
	bigint	&operator>>=(const bigint &other);
	bigint	operator>>(unsigned int n) const;
	bigint	operator>>(const bigint &other) const;

	// 4. Comparison Operators
	bool	operator<(const bigint &other) const;
	bool	operator>(const bigint &other) const;
	bool	operator<=(const bigint &other) const;
	bool	operator>=(const bigint &other) const;
	bool	operator==(const bigint &other) const;
	bool	operator!=(const bigint &other) const;

	// 5. Output
	void	print(std::ostream &os) const;
};

// 6. Global operator (for std::cout << a)
std::ostream
&operator<<(std::ostream &os, const bigint &obj);

#endif