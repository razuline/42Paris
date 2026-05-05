/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:56:34 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/05 14:47:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bigint.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

bigint::bigint()
{
	_digits.push_back(0);

	// std::cout << "Default constructor called" << std::endl;
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

	// std::cout << "Default constructor called" << std::endl;
}

bigint::bigint(const bigint &copy) :
	_digits(copy._digits)
{
	// std::cout << "Copy constructor called" << std::endl;
}

bigint
&bigint::operator=(const bigint &other)
{
	if (this != &other)
		this->_digits = other._digits;
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

bigint::~bigint()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ---------------------------- PRIVATE METHODS ----------------------------- */

/* Ensures the number doesn't have unnecessary zeros at the end of the vector */
void
bigint::_removeLeadingZeros()
{
	while (_digits.size() > 1 && _digits.back() == 0)
	{
		_digits.pop_back();
	}
}

/* Converts the bigint value to a native int (useful for shift amounts) */
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
	size_t	n = std::max(_digits.size(), other._digits.size());

	for (size_t i = 0; i < n || carry; ++i)
	{
		if (i == _digits.size())
			_digits.push_back(0);

		int	sum = _digits[i] + carry +
					(i < other._digits.size() ? other._digits[i] : 0);
		_digits[i] = sum % 10;
		carry = sum / 10;
	}
	return *this;
}

bigint
bigint::operator+(const bigint &other) const
{
	bigint	res(*this);

	res += other;
	return res;
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
	// Shifting 0 left results in 0
	if (n > 0 && !(_digits.size() == 1 && _digits[0] == 0))
	{
		_digits.insert(_digits.begin(), n, 0);
	}
	return *this;
}

bigint
bigint::operator<<(unsigned int n) const
{
	bigint	res(*this);

	res <<= n;
	return res;
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
	return *this;
}

bigint
bigint::operator>>(unsigned int n) const
{
	bigint	res(*this);

	res >>= n;
	return res;
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
	return *this >> other._toInt();
}

/* --- Comparison --- */

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
