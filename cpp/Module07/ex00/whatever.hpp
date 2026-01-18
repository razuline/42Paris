/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:44:39 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 16:20:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

#include <iostream>
#include <string>

// Swaps the values of two given parameters.
// Does not return anything.
template <typename T>
void	swap(T &a, T &b)
{
	T	tmp = a;
	a = b;
	b = tmp;
}

// Compares the two values passed as parameters and returns the smallest one.
// If they are equal, it returns the second one.
template <typename T>
T	min(T a, T b)
{
	return (a < b) ? a : b;
}

// Compares the two values passed as parameters and returns the greatest one.
// If they are equal, it returns the second one.
template <typename T>
T	max(T a, T b)
{
	return (a > b) ? a : b;
}

#endif