/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:46:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/09 18:52:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	pgcd(int a, int b)
{
	int	tmp;

	if (a == 0 || b == 0)
		return (0);
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
	int	a;
	int	b;

	if (ac != 3)
	{
		printf("\n");
		return (0);
	}
	a = atoi(av[1]);
	b = atoi(av[2]);
	if (a <= 0 || b <= 0)
	{
		printf("\n");
		return (0);
	}
	printf("%d\n", pgcd(a, b));
	return (0);
}
