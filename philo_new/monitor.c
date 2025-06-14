/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:16:55 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 18:15:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philo_death(t_data *data, int i)
{
	long	curr_time;
	long	time_since_last_meal;
	bool	should_die;

	pthread_mutex_lock(&data->philos[i].meal_mutex);
	curr_time = get_time();
	time_since_last_meal = curr_time - data->philos[i].last_meal;
	should_die = (time_since_last_meal > data->time_to_die);
	pthread_mutex_unlock(&data->philos[i].meal_mutex);
	if (should_die)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stop_flag)
		{
			data->stop_flag = true;
			pthread_mutex_unlock(&data->stop_mutex);
			print_status(&data->philos[i], DIED);
			return (true);
		}
		pthread_mutex_unlock(&data->stop_mutex);
	}
	return (false);
}

static bool	check_all_ate(t_data *data)
{
	int		fed_count;
	bool	all_fed;

	if (data->max_meals == -1)
		return (false);
	pthread_mutex_lock(&data->meal_mutex);
	fed_count = data->philos_ate_enough;
	pthread_mutex_unlock(&data->meal_mutex);
	all_fed = (fed_count == data->num_philos);
	if (all_fed)
	{
		pthread_mutex_lock(&data->stop_mutex);
		if (!data->stop_flag)
		{
			data->stop_flag = true;
		}
		pthread_mutex_unlock(&data->stop_mutex);
	}
	return (all_fed);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	pthread_barrier_wait(&data->barrier);
	while (!is_simulation_stopped(data))
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (check_philo_death(data, i))
				break ;
		}
		if (check_all_ate(data))
			break ;
		usleep(100);
	}
	return (NULL);
}
