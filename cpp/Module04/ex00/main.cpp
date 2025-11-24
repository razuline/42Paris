/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:25:47 by erazumov          #+#    #+#             */
/*   Updated: 2025/11/24 13:54:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	//const Animal		*meta = new Animal(); "cannot instantiate abstract class"
	const Animal		*i = new Cat();
	const Animal		*j = new Dog();
	const WrongAnimal	*wrong = new WrongCat();

	std::cout << std::endl;
	std::cout << i->getType() << "'getType()'" << std::endl;
	std::cout << j->getType() << "'getType()'" << std::endl;
	std::cout << wrong->getType() << "'getType()'" << std::endl;
	std::cout << std::endl;

	i->makeSound(); // Will output the cat sound!
	j->makeSound();
	wrong->makeSound();
	//meta->makeSound();
	std::cout << std::endl;

	delete i;
	delete j;
	delete wrong;
	return 0;
}
