/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_exam.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:43 by erazumov          #+#    #+#             */
/*   Updated: 2026/05/10 18:01:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_EXAM_HPP
# define BIGINT_EXAM_HPP

# include <iostream>
# include <vector>
# include <algorithm>

class bigint
{
private:
	std::vector<int>	_digits;

	int		_toInt() const;
	void	_removeLeadingZeros();

public:
	bigint();
	bigint(unsigned long long n);
	bigint(const bigint &copy);
	bigint	&operator=(const bigint &other);
	~bigint();

	bigint	&operator+=(const bigint &other);
	bigint	operator+(const bigint &other) const;

	bigint	&operator++();
	bigint	operator++(int);

	bigint	&operator<<=(unsigned int n);
	bigint	operator<<(unsigned int n) const;

	bigint	&operator>>=(unsigned int n);
	bigint	&operator>>=(const bigint &other);
	bigint	operator>>(unsigned int n) const;
	bigint	operator>>(const bigint &other) const;

	bool	operator==(const bigint &other) const;
	bool	operator<(const bigint &other) const;
	bool	operator!=(const bigint &other) const;
	bool	operator<=(const bigint &other) const;
	bool	operator>=(const bigint &other) const;
	bool	operator>(const bigint &other) const;

	void	print(std::ostream &os) const;
};

std::ostream
&operator<<(std::ostream &os, const bigint &obj);

#endif