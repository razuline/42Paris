/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 15:36:07 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	print_usage(void)
{
	printf("Usage: ./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep ");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (print_usage());
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, ac, av) == FAILURE)
	{
		clear_data(&data);
		return (1);
	}
	if (start_simulation(&data) == FAILURE)
	{
		clear_data(&data);
		return (1);
	}
	clear_data(&data);
	return (0);
}
