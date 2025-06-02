/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:25:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 16:20:56 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (printf("Usage: ./philo n_philo t_die t_eat t_sleep "
			"[max_meals]\n"), FAILURE);

	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->max_meals = -1;

	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);

	if (data->num_philos <= 0 || data->time_to_die <= 0
			|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
			|| (ac == 6 && data->max_meals <= 0))
		return (printf("Error: Invalid arguments\n"), FAILURE);

	data->start_time = get_time_in_ms();
	data->is_dead = 0;
	return (SUCCESS);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (printf("Error: Fork mutex allocation failed\n"), FAILURE);

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Error: Fork mutex init failed\n"), FAILURE);
		i++;
	}

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (printf("Error: Print mutex init failed\n"), FAILURE);

	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (printf("Error: Meal mutex init failed\n"), FAILURE);

	return (SUCCESS);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("Error: Philosophers allocation failed\n"), FAILURE);

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;

		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		i++;
	}
	return (SUCCESS);
}
