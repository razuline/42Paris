/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:56:34 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/20 13:30:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bigint.hpp"

/* ------------------------- ORTHODOX CANONICAL FORM ------------------------ */

Bigint::Bigint(unsigned long long n)
{
	if (n == 0)
		_v.push_back(0);

	while (n > 0)
	{
		_v.push_back(n % 10);
		n /= 10;
	}

	// std::cout << "Default constructor called" << std::endl;
}

Bigint::Bigint(const Bigint &copy) :
	_v(copy._v)
{
	// std::cout << "Copy constructor called" << std::endl;
}

Bigint
&Bigint::operator=(const Bigint &other)
{
	if (this != &other)
	{
		this->_v = other._v;
	}
	return *this;

	// std::cout << "Copy assignment operator called" << std::endl;
}

Bigint::~Bigint()
{
	// std::cout << "Destructor called" << std::endl;
}

/* ------------------------------ CORE METHODS ------------------------------ */

void
Bigint::print(std::ostream &os) const
{
	for (int i = _v.size() - 1; i >= 0; i--)
	{
		os << _v[i];
	}
}

std::ostream
&operator<<(std::ostream &os, const Bigint &obj)
{
	obj.print(os);
	return os;
}
