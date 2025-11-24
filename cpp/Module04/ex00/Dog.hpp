/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:26:54 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:20:02 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include <iostream>
# include <string>

# include "Animal.hpp"

class Dog : virtual public Animal
{
public:
	Dog(void);
	Dog &operator=(const Dog &other);
	~Dog(void);

	// --- Member Functions ---
	void	makeSound(void) const;
};

#endif