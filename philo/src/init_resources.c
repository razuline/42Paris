/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:42:55 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/06 16:04:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (error_exit(data, "Error: Fork mutex allocation failed",
				ERR_MALLOC));
	i = -1;
	while (++i < data->num_philos)
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_exit(data, "Error: Fork mutex init failed",
					ERR_MUTEX));
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (error_exit(data, "Error: Print mutex init failed", ERR_MUTEX));
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (error_exit(data, "Error: Meal mutex init failed", ERR_MUTEX));
	return (SUCCESS);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (error_exit(data, "Error: Philosophers allocation failed",
				ERR_MALLOC));
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].data = data;
	}
	return (SUCCESS);
}

int	init_resources(t_data *data)
{
	if (init_forks(data) != SUCCESS)
		return (FAILURE);
	if (init_philos(data) != SUCCESS)
	{
		free(data->forks);
		return (FAILURE);
	}
	return (SUCCESS);
}
