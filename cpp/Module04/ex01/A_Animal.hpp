/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:51:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:53:22 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_ANIMAL_HPP
# define A_ANIMAL_HPP

# include <iostream>
# include <string>

class A_Animal
{
protected:
	std::string	_type;

public:
	A_Animal(void);
	A_Animal(const A_Animal &copy);
	A_Animal &operator=(const A_Animal &other);
	// Without virtual, 'delete animal_pointer' would only call ~Animal(),
		// skipping ~Cat() or ~Dog(), causing a memory leak of the Brain.
	virtual ~A_Animal(void);

	// --- Getters ---
	std::string		getType(void) const;

	// --- Member Functions ---
	virtual void	makeSound(void) const = 0; // pure virtual
};

#endif