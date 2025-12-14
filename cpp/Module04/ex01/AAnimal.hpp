/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A_Animal.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:51:36 by erazumov          #+#    #+#             */
/*   Updated: 2025/12/01 13:32:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_ANIMAL_HPP
# define A_ANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal
{
protected:
	std::string	_type;

public:
	AAnimal(void);
	AAnimal(const AAnimal &copy);
	AAnimal &operator=(const AAnimal &other);
	// Without virtual, 'delete animal_pointer' would only call ~Animal(),
		// skipping ~Cat() or ~Dog(), causing a memory leak of the Brain.
	virtual ~AAnimal(void);

	// --- Getters ---
	std::string		getType(void) const;

	// --- Member Functions ---
	virtual void	makeSound(void) const = 0; // pure virtual
};

#endif