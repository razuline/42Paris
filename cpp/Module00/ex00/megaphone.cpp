/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:39:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/07/05 14:40:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <iostream>

int	main(int ac, char **av)
{
	int	i, j;

	if (ac > 1)
	{
		for (i = 1; i < ac; i++)
		{
			j = 0;
			for (; av[i][j] != '\0'; j++)
				std::cout << static_cast<char>(toupper(av[i][j]));
		}
		std::cout << std::endl;
	}
	else
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
}
