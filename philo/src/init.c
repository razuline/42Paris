/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:25:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 16:11:48 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i]);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	init_mutexes(t_data *data)
{
	if (!data)
		return (ERROR);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (ERROR);
	}
	return (init_forks(data));
}

static void	setup_philo(t_data *data, int index)
{
	data->philos[index].philo_id = index + 1;
	data->philos[index].meals_eaten = 0;
	data->philos[index].last_meal_time = 0;
	data->philos[index].left_fork = &data->forks[index];
	data->philos[index].right_fork = &data->forks[(index + 1)
		% data->number_of_philosophers];
	data->philos[index].data = data;
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->philos || !data->forks)
		return (ERROR);
	while (i < data->number_of_philosophers)
	{
		setup_philo(data, i);
		i++;
	}
	return (SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || !data)
		return (ERROR);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->must_eat_count = -1;
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->must_eat_count <= 0))
		return (ERROR);
	data->someone_died = 0;
	data->philos_ate_enough = 0;
	data->start_time = get_time();
	if (alloc_resources(data) != SUCCESS)
		return (ERROR);
	if (init_mutexes(data) != SUCCESS)
		return (clear_data(data), ERROR);
	if (init_philos(data) != SUCCESS)
		return (clear_data(data), ERROR);
	return (SUCCESS);
}
