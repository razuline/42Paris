/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:51:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 19:24:17 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal
{
protected:
	std::string	_type;

public:
	Animal(void);
	Animal(const Animal &copy);
	Animal &operator=(const Animal &other);
	// Without virtual, 'delete animal_pointer' would only call ~Animal(),
		// skipping ~Cat() or ~Dog(), causing a memory leak of the Brain.
	virtual ~Animal(void);

	// --- Getters ---
	std::string		getType(void) const;

	// --- Member Functions ---
	virtual void	makeSound(void) const = 0;
};

#endif