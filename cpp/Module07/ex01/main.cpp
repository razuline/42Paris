/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:47:18 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/18 17:58:21 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include <string>

int	main(void)
{
	// Test with an array of integers
	int			intArray[] = {1, 2, 3, 4, 5};
	size_t		intLen = sizeof(intArray) / sizeof(int);

	std::cout << "Int array: ";
	::iter(intArray, intLen, printElement<int>);
	std::cout << std::endl;

	// Test with an array of strings
	std::string	strArray[] = {"Hello", "world", "42"};
	size_t		strLen = 3;

	std::cout << "String array: ";
	::iter(strArray, strLen, printElement<std::string>);
	std::cout << std::endl;

	// Test with a constant array
	const int	constArray[] = {10, 20, 30};
	std::cout << "Const int array: ";
	::iter(constArray, 3, printElementConst<int>);
	std::cout << std::endl;

	return 0;
}
