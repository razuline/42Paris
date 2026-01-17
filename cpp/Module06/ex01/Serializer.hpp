/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:36:29 by erazumov          #+#    #+#             */
/*   Updated: 2026/01/17 16:55:36 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

# include <iostream>
# include <stdint.h> // uintptr_t
# include "Data.hpp"

class Serializer
{
private:
	// --- Orthodox Canonical Form ---
	Serializer();
	Serializer(const Serializer &src);
	Serializer &operator=(const Serializer &rhs);
	~Serializer();

public:
	// --- Static Methods ---
	// Converts a pointer to an unsigned integer type
	static uintptr_t	serialize(Data *ptr);
	// Converts an unsigned integer back to a Data pointer
	static Data			*deserialize(uintptr_t raw);
};

#endif