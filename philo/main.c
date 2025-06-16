/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:58:12 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 21:12:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error: Invalid number of arguments.\n");
		printf("Usage: ./philo num_philos t_die t_eat t_sleep [n_meals]\n");
		return (1);
	}
	if (init_data(&data, ac, av) != 0)
		return (1);
	if (start_simulation(&data) != 0)
	{
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
