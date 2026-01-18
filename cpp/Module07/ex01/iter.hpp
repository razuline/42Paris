/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:20:24 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 17:56:34 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>
#include <string>

// Iterates through an array and applies a function to each element.
// arr: the address of an array.
// len: the length of the array, passed as a const value.
// func: a function pointer to be applied to each element.
template <typename T, typename F>
void	iter(T *arr, size_t len, F func)
{
	if (!arr || !func)
		return;
	for (size_t i = 0; i < len; i++)
		func(arr[i]);
}

// Function template to be used with iter.
// const allows both const and non-const arrays.
template <typename T>
void	printElement(T &content)
{
	std::cout << content << " ";
}

// Function template for const elements.
template <typename T>
void	printElementConst(const T &content)
{
	std::cout << content << " ";
}

#endif