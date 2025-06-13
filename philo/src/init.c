/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:38:15 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/13 12:13:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int ac, char **av)
{
	if (safe_atoi(av[1], &data->num_philos) != SUCCESS || data->num_philos <= 0)
		return (error_exit(data, "Error: Invalid philosopher count", ERR_ARGS));
	if (parse_time_value(av[2], &data->time_to_die) != SUCCESS
		|| data->time_to_die <= 0)
		return (error_exit(data, "Error: Invalid time_to_die", ERR_ARGS));
	if (parse_time_value(av[3], &data->time_to_eat) != SUCCESS
		|| data->time_to_eat <= 0)
		return (error_exit(data, "Error: Invalid time_to_eat", ERR_ARGS));
	if (parse_time_value(av[4], &data->time_to_sleep) != SUCCESS
		|| data->time_to_sleep < 0)
		return (error_exit(data, "Error: Invalid time_to_sleep", ERR_ARGS));
	if (ac == 6 && (safe_atoi(av[5], &data->max_meals) != SUCCESS
			|| data->max_meals <= 0))
		return (error_exit(data, "Error: Invalid max_meals", ERR_ARGS));
	return (SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	data->max_meals = -1;
	data->philos_ate_enough = 0;
	if (ac != 5 && ac != 6)
		return (error_exit(data, "Usage: ./philo n t_die t_eat t_sleep [meals]",
				ERR_ARGS));
	if (parse_args(data, ac, av) != SUCCESS)
		return (FAILURE);
	data->start_time = get_time();
	return (SUCCESS);
}

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
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (error_exit(data, "Error: Stop mutex init failed", ERR_MUTEX));
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
