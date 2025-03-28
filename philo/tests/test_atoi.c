/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:47:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/03/28 12:12:44 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef TEST

# include "../includes/philo.h"

int	ft_atoi(char *str);

int	main(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 2)
		return (printf("Usage: %s <number>\n", av[0]), 1);
	if (av[1][0] == '\0')
		return (printf("Error: Empty string\n"), 1);
	if (av[1][i] == '+')
		i++;
	while (av[1][i])
	{
		if (av[1][i++] < '0' || av[1][i - 1] > '9')
			return (printf("Error: Positive number required\n"), 1);
	}
	printf("Result: %d\n", ft_atoi(av[1]));
	return (0);
}

#endif