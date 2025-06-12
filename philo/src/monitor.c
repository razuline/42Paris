/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:16:55 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/12 22:49:16 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_philo_death(t_data *data, int i)
{
	long	curr_time;
	long	time_since_last_meal;
	bool	should_die;

	pthread_mutex_lock(&data->meal_mutex);
	curr_time = get_time();
	time_since_last_meal = curr_time - data->philos[i].last_meal;
	should_die = (time_since_last_meal >= data->time_to_die);
	pthread_mutex_unlock(&data->meal_mutex);
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
	int	fed_count;

	if (data->max_meals == -1)
		return (false);
	pthread_mutex_lock(&data->meal_mutex);
	fed_count = data->philos_ate_enough;
	pthread_mutex_unlock(&data->meal_mutex);
	return (fed_count == data->num_philos);
}

void	monitor_simulation(t_data *data)
{
	int		i;
	bool	all_ate_enough;

	while (true)
	{
		i = -1;
		all_ate_enough = true;
		while (++i < data->num_philos)
		{
			if (check_philo_death(data, i))
				return ;
			if (data->max_meals != -1)
			{
				pthread_mutex_lock(&data->meal_mutex);
				if (data->philos[i].meals_eaten < data->max_meals)
					all_ate_enough = false;
				pthread_mutex_unlock(&data->meal_mutex);
			}
		}
		if (data->max_meals != -1 && all_ate_enough)
		{
			pthread_mutex_lock(&data->stop_mutex);
			data->stop_flag = true;
			pthread_mutex_unlock(&data->stop_mutex);
			return ;
		}
		usleep(1000);
	}
}
