/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:07:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/05/13 18:15:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	int	a;
	int	b;
	int	result;

	if (ac != 4)
	{
		printf("\n");
		return (0);
	}
	a = atoi(av[1]);
	b = atoi(av[3]);
	if (av[2][0] == '+')
		result = a + b;
	else if (av[2][0] == '-')
		result = a - b;
	else if (av[2][0] == '*')
		result = a * b;
	else if (av[2][0] == '/')
		result = a / b;
	else if (av[2][0] == '%')
		result = a % b;
	else
	{
		printf("\n");
		return (0);
	}
	printf("%d\n", result);
	return (0);
}
