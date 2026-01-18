/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:44:23 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 16:25:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>

int	main(void)
{
	int	a = 2;
	int	b = 3;

	std::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << std::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << std::max(a, b) << std::endl;

	std::cout << "-------------------------------------" << std::endl;

	std::string	c = "chaine1";
	std::string	d = "chaine2";

	std::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << std::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << std::max(c, d) << std::endl;

	return 0;
}

// Should output:
// a = 3, b = 2
// min(a, b) = 2
// max(a, b) = 3
// -------------------------------------
// c = chaine2, d = chaine1
// min(c, d) = chaine1
// max(c, d) = chaine2