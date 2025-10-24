/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 11:58:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/10/24 15:00:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Fixed
calculateSide(Point const p1, Point const p2, Point const test_point)
{
	// Récupérer les coordonnées via les getters
	Fixed	p1_x = p1.getX();
	Fixed	p1_y = p1.getY();
	Fixed	p2_x = p2.getX();
	Fixed	p2_y = p2.getY();
	Fixed	test_x = test_point.getX();
	Fixed	test_y = test_point.getY();

	// Appliquer la formule mathématique en utilisant les opérateurs surchargés
	// Formule : (x_test - x1) * (y2 - y1) - (y_test - y1) * (x2 - x1)
	Fixed	result = (test_x - p1_x) * (p2_y - p1_y)
					- (test_y - p1_y) * (p2_x - p1_x);

	return result;
}

bool
bsp(Point const a, Point const b, Point const c, Point const point)
{
	// Calcul pour l'arête a -> b
	Fixed	side1 = calculateSide(a, b, point);
	// Calcul pour l'arête b -> c
	Fixed	side2 = calculateSide(b, c, point);
	// Calcul pour l'arête c -> a
	Fixed	side3 = calculateSide(c, a, point);

	// Cas 1 : Tous les résultats sont positifs
	bool	all_positive = (side1 > Fixed(0)
							&& side2 > Fixed(0)
							&& side3 > Fixed(0));

	// Cas 2 : Tous les résultats sont négatifs
	bool	all_negative = (side1 < Fixed(0)
							&& side2 < Fixed(0)
							&& side3 < Fixed(0));

	// Si l'un des deux cas est vrai, le point est à l'intérieur
	if (all_positive || all_negative)
		return true;
	
	// Dans tous les autres cas (signes mixtes ou un zéro),
	// le point est à l'extérieur
	return false;
}
