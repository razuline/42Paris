/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 16:41:25 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (printf("Error: Thread creation failed\n"), FAILURE);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_detach(data->philos[i].thread) != 0)
			return (printf("Error: Thread detach failed\n"), FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	monitor_simulation(t_data *data)
{
	int		i;
	int		all_ate_enough;
	long	curr_time;

	while (1)
	{
		all_ate_enough = 1;
		curr_time = get_time_in_ms();
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (curr_time - data->philos[i].last_meal_time >= data->time_to_die)
			{
				print_status(&data->philos[i], DIED);
				pthread_mutex_unlock(&data->meal_mutex);
				data->is_dead = 1;
				return ;
			}
			if (data->max_meals != -1 && data->philos[i].meals_eaten < data->max_meals)
				all_ate_enough = 0;
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (data->max_meals != -1 && all_ate_enough)
		{
			printf("All philosophers ate %d times\n", data->max_meals);
			return ;
		}
		usleep(1000);
	}
}
