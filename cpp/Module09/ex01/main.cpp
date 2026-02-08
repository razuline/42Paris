/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:14:16 by erazumov          #+#    #+#             */
/*   Updated: 2026/02/08 15:33:13 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int ac, char **av)
{
	// 1. Check if the user provided exactly one argument
	// As required by the constraints
	if (ac != 2)
	{
		std::cerr << "Error" << std::endl;
		return 1;
	}

	// 2. Instantiate the RPN class
	RPN	rpn;

	// 3. Process the expression
	// The program must handle operations with "+ - / *" tokens
	rpn.calculate(av[1]);

	return 0;
}
