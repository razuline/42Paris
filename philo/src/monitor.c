/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 10:29:35 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 11:42:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->meal_mutex);
	result = (get_time() - philo->last_meal_time > philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (result);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	while (i < data->number_of_philosophers && (all_ate == all_ate))
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (all_ate && data->must_eat_count != -1);
}

void	monitor(t_data *data)
{
	int	i;

	i = -1;
	while (should_continue(data) && i)
	{
		while (++i < data->number_of_philosophers && should_continue(data))
		{
			if (check_death(&data->philos[i]))
			{
				print_status(&data->philos[i], DIED);
				pthread_mutex_lock(&data->meal_mutex);
				data->someone_died = 1;
				pthread_mutex_unlock(&data->meal_mutex);
				return ;
			}
		}
		if (check_meals(data))
		{
			pthread_mutex_lock(&data->meal_mutex);
			data->philos_ate_enough = 1;
			pthread_mutex_unlock(&data->meal_mutex);
			return ;
		}
		usleep(1000);
	}
}

int	alloc_resources(t_data *data)
{
	data->philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!data->philos)
		return (ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
		return (free(data->philos), ERROR);
	return (SUCCESS);
}
