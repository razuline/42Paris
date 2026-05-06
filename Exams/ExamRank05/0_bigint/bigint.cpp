/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:56:34 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/06 13:48:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

bigint::bigint()
{
	_digits.push_back(0);
}

bigint::bigint(unsigned long long n)
{
	if (n == 0)
		_digits.push_back(0);

	while (n > 0)
	{
		_digits.push_back(n % 10);
		n /= 10;
	}
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

void
bigint::_removeLeadingZeros()
{
	// Keep at least one digit, even if it's zero
	while (_digits.size() > 1 && _digits.back() == 0)
		_digits.pop_back();
}

int
bigint::_toInt() const
{
	int	res = 0;
	int	base = 1;

	for (size_t i = 0; i < _digits.size(); ++i)
	{
		res += _digits[i] * base;
		base *= 10;
	}
	return res;
}

/* ----------------------------- PUBLIC METHODS ----------------------------- */

/* --- Arithmetic --- */

bigint
&bigint::operator+=(const bigint &other)
{
	int	carry = 0;
	size_t	maxSize = std::max(_digits.size(), other._digits.size());

	for (size_t i = 0; i < maxSize || carry; ++i)
	{
		if (i == _digits.size())
			_digits.push_back(0);

		int	currOther = (i < other._digits.size()) ? other._digits[i] : 0;
		int	sum = _digits[i] + currOther + carry;

		_digits[i] = sum % 10;
		carry = sum / 10;
	}
	return *this;
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
	// Shifting 0 remains 0
	if (n > 0 && !(_digits.size() == 1 && _digits[0] == 0))
		_digits.insert(_digits.begin(), n, 0);
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
	if (n >= _digits.size())
	{
		_digits.clear();
		_digits.push_back(0);
	}
	else
	{
		_digits.erase(_digits.begin(), _digits.begin() + n);
	}
	_removeLeadingZeros();
	return *this;
}

bigint
bigint::operator>>(unsigned int n) const
{
	return bigint(*this) >>= n;
}

/* --- Overloads for bigint parameters --- */

bigint
&bigint::operator>>=(const bigint &other)
{
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
