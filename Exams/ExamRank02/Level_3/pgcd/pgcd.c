/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:46:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/17 13:58:01 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	pgcd(int a, int b)
{
	int	tmp;

	while (b != 0)
	{
		tmp = b;
		b = a % b;
		a = tmp;
	}
	return (a);
}

int	main(int ac, char **av)
{
	int	num1;
	int	num2;

	if (ac != 3)
	{
		printf("\n");
		return (0);
	}
	num1 = atoi(av[1]);
	num2 = atoi(av[2]);
	if (num1 <= 0 || num2 <= 0)
	{
		printf("\n");
		return (0);
	}
	printf("%d\n", pgcd(num1, num2));
	return (0);
}
