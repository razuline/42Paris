/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 15:09:15 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/25 15:41:47 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

int	main(void)
{
	// 1. Définir les sommets du triangle
	Point a(0.0f, 0.0f);
	Point b(10.0f, 0.0f);
	Point c(0.0f, 10.0f);

	// 2. Définir les points à tester
	Point point_inside(2.0f, 2.0f);
	Point point_outside(15.0f, 15.0f);
	Point point_on_edge(5.0f, 0.0f);
	Point point_on_vertex(0.0f, 0.0f);

	// --- Test 1: Point à l'intérieur ---
	std::cout << "Le point (2, 2) est à l'intérieur ? ";
	if (bsp(a, b, c, point_inside))
		std::cout << "Oui" << std::endl;
	else
		std::cout << "Non" << std::endl;

	// --- Test 2: Point à l'extérieur ---
	std::cout << "Le point (15, 15) est à l'intérieur ? ";
	if (bsp(a, b, c, point_outside))
		std::cout << "Oui" << std::endl;
	else
		std::cout << "Non" << std::endl;

	// --- Test 3: Point sur une arête ---
	std::cout << "Le point (5, 0) est à l'intérieur ? ";
	if (bsp(a, b, c, point_on_edge))
		std::cout << "Oui" << std::endl;
	else
		std::cout << "Non" << std::endl;

	// --- Test 4: Point sur un sommet ---
	std::cout << "Le point (0, 0) est à l'intérieur ? ";
	if (bsp(a, b, c, point_on_vertex))
		std::cout << "Oui" << std::endl;
	else
		std::cout << "Non" << std::endl;

	return 0;
}
