/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:16:55 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/07 14:26:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_simulation_end(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

static bool	check_philo_death(t_data *data, int i)
{
	size_t	curr_time;
	long	time_since_meal;

	pthread_mutex_lock(&data->meal_mutex);
	curr_time = get_time();
	time_since_meal = curr_time - data->philos[i].last_meal;
	if (time_since_meal > data->time_to_die)
	{
		print_status(&data->philos[i], "died");
		pthread_mutex_lock(&data->stop_mutex);
		data->stop_flag = true;
		pthread_mutex_unlock(&data->stop_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

static bool	check_meals_complete(t_data *data)
{
	int	i;

	if (data->max_meals == -1)
		return (false);
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->meal_mutex);
	}
	return (true);
}

void	monitor_simulation(t_data *data)
{
	int	i;

	while (!check_simulation_end(data))
	{
		i = -1;
		while (++i < data->num_philos)
		{
			if (check_philo_death(data, i))
				return ;
		}
		if (check_meals_complete(data))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("All philosophers ate %d times\n", data->max_meals);
			pthread_mutex_unlock(&data->print_mutex);
			return ;
		}
		usleep(1000);
	}
}
