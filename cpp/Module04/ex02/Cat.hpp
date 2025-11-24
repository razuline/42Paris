/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:23:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 22:23:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include <string>

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal
{
private:
	// Pointer to Brain. Must be allocated with 'new' and freed with 'delete'.
	Brain	*_brain;

public:
	Cat(void);
	// We need custom copy constructor and assignment operator
		// to ensure Deep Copy of the _brain pointer.
	Cat(const Cat &copy);
	Cat &operator=(const Cat &other);
	virtual ~Cat(void); // Overrides base destructor

	// --- Member Functions ---
	virtual void	makeSound(void) const;

	// Helper to test deep copy
	Brain	*getBrain() const { return _brain; }
};

#endif