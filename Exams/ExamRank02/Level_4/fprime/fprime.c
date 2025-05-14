/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprime.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:01:25 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/10 14:02:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	fprime(int n)
{
	int	first;
	int	prime;

	if (n == 1)
	{
		printf("1");
		return ;
	}
	first = 1;
	prime = 2;
	while (n > 1)
	{
		while (n % prime == 0)
		{
			if (first == 0)
				printf("*");
			printf("%d", prime);
			first = 0;
			n /= prime;
		}
		prime++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		fprime(atoi(av[1]));
	printf("\n");
	return (0);
}
