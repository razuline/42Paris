/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:23:26 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:19:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include <iostream>
# include <string>

# include "Animal.hpp"

class Cat : virtual public Animal
{
public:
	Cat(void);
	Cat &operator=(const Cat &other);
	~Cat(void);

	// --- Member Functions ---
	void	makeSound(void) const;
};

#endif