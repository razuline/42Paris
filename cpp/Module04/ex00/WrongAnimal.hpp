/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:36:01 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:39:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal
{
protected:
	std::string	_type;

public:
	WrongAnimal(void);
	~WrongAnimal(void);

	// --- Getters ---
	std::string	getType(void) const;

	// --- Member Functions ---
	void makeSound(void) const; // Not virtual!
};

#endif