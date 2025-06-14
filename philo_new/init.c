/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:15 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 18:19:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo n t_die t_eat t_sleep [meals]\n");
		return (FAILURE);
	}
	if (safe_atoi(av[1], &data->num_philos) != SUCCESS || data->num_philos <= 0)
		return (error_exit(data, "Error: Invalid philosopher count", ERR_ARGS));
	if (parse_time_value(av[2], &data->time_to_die) != SUCCESS
		|| data->time_to_die <= 0)
		return (error_exit(data, "Error: Invalid time_to_die", ERR_ARGS));
	if (parse_time_value(av[3], &data->time_to_eat) != SUCCESS
		|| data->time_to_eat <= 0)
		return (error_exit(data, "Error: Invalid time_to_eat", ERR_ARGS));
	if (parse_time_value(av[4], &data->time_to_sleep) != SUCCESS
		|| data->time_to_sleep <= 0)
		return (error_exit(data, "Error: Invalid time_to_sleep", ERR_ARGS));
	if (ac == 6)
	{
		if (safe_atoi(av[5], &data->max_meals) != SUCCESS
			|| data->max_meals < 0)
			return (error_exit(data, "Error: Invalid max_meals", ERR_ARGS));
	}
	else
		data->max_meals = -1;
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
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (error_exit(data, "Error: Philo meal mutex init failed",
					ERR_MUTEX));
	}
	return (SUCCESS);
}

int	init_resources(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (error_exit(data, "Error: Forks allocation failed", ERR_MALLOC));
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (error_exit(data, "Error: Fork mutex init failed",
					ERR_MUTEX));
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (error_exit(data, "Error: Print mutex init failed", ERR_MUTEX));
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (error_exit(data, "Error: Meal mutex init failed", ERR_MUTEX));
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (error_exit(data, "Error: Stop mutex init failed", ERR_MUTEX));
	if (pthread_barrier_init(&data->barrier, NULL, data->num_philos + 1) != 0)
		return (error_exit(data, "Error: Barrier init failed", ERR_MUTEX));
	return (SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	if (parse_args(data, ac, av) != SUCCESS)
		return (FAILURE);
	if (init_philos(data) != SUCCESS)
		return (FAILURE);
	data->stop_flag = false;
	data->philos_ate_enough = 0;
	return (SUCCESS);
}
