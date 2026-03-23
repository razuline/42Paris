/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bigint.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:43 by erazumov          #+#    #+#             */
/*   Updated: 2026/03/20 13:29:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGINT_HPP
# define BIGINT_HPP

# include <iostream>
# include <vector>
# include <algorithm>

class Bigint
{
private:
	std::vector<int>	_v;

public:
	/* --- Orthodox Canonical Form --- */
	Bigint(unsigned long long n = 0);
	Bigint	&operator=(const Bigint &other);
	Bigint(const Bigint &copy);
	~Bigint();

	/* --- Core Methods --- */
	void	print(std::ostream &os) const;
};

std::ostream
&operator<<(std::ostream &os, const Bigint &obj);

#endif