/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:26:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:44:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include <string>

# include "A_Animal.hpp"
# include "Brain.hpp"

class Dog : public A_Animal
{
private:
	Brain	*_brain;

public:
	Dog(void);
	Dog(const Dog &copy);
	Dog &operator=(const Dog &other);
	virtual ~Dog(void);

	// --- Member Functions ---
	virtual void	makeSound(void) const;

	// Helper to test deep copy
	Brain	*getBrain() const { return _brain; }
};

#endif