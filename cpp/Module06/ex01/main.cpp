/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:49:53 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 17:02:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

#include <iostream>

int	main(void)
{
	// 1. Initialise a Data object with some values
	Data	myData;

	myData.id = 42;
	myData.name = "erazumov";
	myData.value = "C++ Module06";

	// 2. Perform serialization
	Data		*originalPtr = &myData;
	uintptr_t	raw = Serializer::serialize(originalPtr);

	// 3. Perform deserialization
	Data		*resultPtr = Serializer::deserialize(raw);

	// 4. Verification
	std::cout << "Original Pointer:     " << originalPtr << std::endl;
	std::cout << "Serialized Value:     " << raw << std::endl;
	std::cout << "Deserialized Pointer: " << resultPtr << std::endl;

	if (resultPtr == originalPtr)
	{
		std::cout << "\n✅ SUCCESS: The pointers match!" << std::endl;
		std::cout << "Data ID:    " << resultPtr->id << std::endl;
		std::cout << "Data Name:  " << resultPtr->name << std::endl;
	}
	else
	{
		std::cout << "\n❌ ERROR: Pointer mismatch!" << std::endl;
		return 1;
	}

	return 0;
}
