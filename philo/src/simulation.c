/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/03 14:43:45 by erazumov         ###   ########.fr       */
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

static bool	check_philo_death(t_data *data, int i, uint64_t curr_time)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(&data->meal_mutex);
	if (curr_time - data->philos[i].last_meal_time >= data->time_to_die)
	{
		print_status(&data->philos[i], DIED);
		data->is_dead = true;
		is_dead = true;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (is_dead);
}

static bool	check_meals_limit(t_data *data)
{
	int		i;
	bool	all_ate_enough;

	all_ate_enough = true;
	pthread_mutex_lock(&data->meal_mutex);
	if (data->max_meals == -1)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		return (false);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->max_meals)
		{
			all_ate_enough = false;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&data->meal_mutex);
	if (all_ate_enough)
		printf("All philosophers ate %d times\n", data->max_meals);
	return (all_ate_enough);
}

static bool	check_simulation_end(t_data *data)
{
	int			i;
	uint64_t	curr_time;

	curr_time = get_time_in_ms();
	i = 0;
	while (i < data->num_philos)
	{
		if (check_philo_death(data, i, curr_time))
			return (true);
		i++;
	}
	return (check_meals_limit(data));
}

void	monitor_simulation(t_data *data)
{
	while (true)
	{
		if (check_simulation_end(data))
			break ;
		usleep(1000);
	}
}
