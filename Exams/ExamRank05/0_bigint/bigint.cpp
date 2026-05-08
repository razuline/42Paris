/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:56:34 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/08 14:15:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

bigint::bigint()
{
	_digits.push_back(0);
}

/*
 * This function "breaks" a normal number into a vector.
 */
bigint::bigint(unsigned long long n)
{
	// Handle the base case where the input is 0
	if (n == 0)
		_digits.push_back(0);

	// Extract digits one by one using modulo and division
	while (n > 0)
	{
		// n % 10 gets the last digit (e.g., 1337 % 10 = 7)
		_digits.push_back(n % 10);

		// n /= 10 removes the last digit (e.g., 1337 / 10 = 133)
		n /= 10;
	}
	// Result for 1337: _digits is {7, 3, 3, 1} (reversed order)
}

bigint::bigint(const bigint &copy) :
	_digits(copy._digits)
{
}

bigint
&bigint::operator=(const bigint &other)
{
	if (this != &other)
		_digits = other._digits;
	return *this;
}

bigint::~bigint()
{
}

/* ---------------------------- PRIVATE METHODS ----------------------------- */

/*
 * This is a specific helper used to handle the exam main
 * where a bigint is used as a shift parameter.
 */
int
bigint::_toInt() const
{
	int	res = 0;
	int	base = 1;

	// Reconstruct the number by multiplying each digit by its power of 10
	for (size_t i = 0; i < _digits.size(); ++i)
	{
		// Result = digit * (1, 10, 100, etc.)
		res += _digits[i] * base;
		base *= 10;
	}
	return res;
}

void
bigint::_removeLeadingZeros()
{
	// Keep at least one digit, even if it's zero
	while (_digits.size() > 1 && _digits.back() == 0)
		_digits.pop_back();
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

/* --- Arithmetic --- */

/*
 * The "column addition" logic.
 */
bigint
&bigint::operator+=(const bigint &other)
{
	int	carry = 0; // Stores the 1 if a column sum is >= 10
	size_t	maxSize = std::max(_digits.size(), other._digits.size());

	// Loop through each column or as long as there is a remaining carry
	for (size_t i = 0; i < maxSize || carry; ++i)
	{
		// If curr number is shorter than the result needs to be,
		// add a new digit (0) to expand it
		if (i == _digits.size())
			_digits.push_back(0);

		// Get digit from the other number; if it's shorter, use 0
		int	currOther = (i < other._digits.size()) ? other._digits[i] : 0;

		// Calculate the total for this column
		int	sum = _digits[i] + currOther + carry;

		// Use modulo (%) to keep only the single digit (e.g., 13 % 10 = 3)
		_digits[i] = sum % 10;

		// Use division (/) to find the new carry (e.g., 13 / 10 = 1)
		carry = sum / 10;
	}
	return *this; // Return the updated object to allow chaining
}

bigint
bigint::operator+(const bigint &other) const
{
	return bigint(*this) += other;
}

/* --- Increment --- */

// Prefix increment
bigint
&bigint::operator++()
{
	return *this += 1;
}

// Postfix increment
bigint
bigint::operator++(int)
{
	bigint	tmp(*this);

	++(*this);
	return tmp;
}

/* --- Digitshift --- */

bigint
&bigint::operator<<=(unsigned int n)
{
	// Rule: Shifting 0 left by any amount is still 0
	if (n > 0 && !(_digits.size() == 1 && _digits[0] == 0))
	{
		// In a reverse vector, adding zeros at the END of a number
		// actually means inserting them at the START of the vector.
		// e.g., 42 is {2, 4}
		// (42 << 2) is 4200, which is {0, 0, 4, 2}
		_digits.insert(_digits.begin(), n, 0);
	}
	return *this;
}

bigint
bigint::operator<<(unsigned int n) const
{
	return bigint(*this) <<= n;
}

bigint
&bigint::operator>>=(unsigned int n)
{
	// If shift amount is larger than the number of digits, the result is 0
	if (n >= _digits.size())
	{
		_digits.clear();
		_digits.push_back(0);
	}
	else
	{
		// Erasing the first 'n' elements removes the lowest powers of 10
		// e.g., 1337 is {7, 3, 3, 1}
		// (1337 >> 2) removes {7, 3}, leaving {3, 1} (13)
		_digits.erase(_digits.begin(), _digits.begin() + n);
	}
	// Clean up any zeros that were left at the high-power end (the end of vector)
	_removeLeadingZeros();
	return *this;
}

bigint
bigint::operator>>(unsigned int n) const
{
	return bigint(*this) >>= n;
}

/* --- Overloads for bigint parameters --- */

/*
 * This allows the syntax: d >>= (const bigint)2.
 */
bigint
&bigint::operator>>=(const bigint &other)
{
	// Convert the 'other' BigInt to a standard int, then shift
	return *this >>= other._toInt();
}

bigint
bigint::operator>>(const bigint &other) const
{
	return bigint(*this) >>= other;
}

/* --- Comparison --- */

bool
bigint::operator<(const bigint &other) const
{
	if (_digits.size() != other._digits.size())
		return _digits.size() < other._digits.size();

	for (int i = _digits.size() - 1; i >= 0; --i)
	{
		if (_digits[i] != other._digits[i])
			return _digits[i] < other._digits[i];
	}
	return false;
}

bool
bigint::operator==(const bigint &other) const
{
	return _digits == other._digits;
}

bool
bigint::operator!=(const bigint &other) const
{
	return !(*this == other);
}

bool
bigint::operator<=(const bigint &other) const
{
	return *this < other || *this == other;
}

bool
bigint::operator>(const bigint &other) const
{
	return !(*this <= other);
}

bool
bigint::operator>=(const bigint &other) const
{
	return !(*this < other);
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
bigint::print(std::ostream &os) const
{
	// Start from the last index (highest power) and go down to 0
	for (int i = _digits.size() - 1; i >= 0; --i)
	{
		os << _digits[i];
	}
}

std::ostream
&operator<<(std::ostream &os, const bigint &obj)
{
	obj.print(os);
	return os;
}
