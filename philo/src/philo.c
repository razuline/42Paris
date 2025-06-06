/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/06 18:04:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_mutex);
}

static bool	check_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	if (data->stop_flag)
	{
		pthread_mutex_unlock(&data->stop_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->stop_mutex);
	return (false);
}

static bool	check_philo_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (get_time() - data->philos[i].last_meal > data->time_to_die)
		{
			print_status(&data->philos[i], DIED);
			set_simulation_stop(data);
			pthread_mutex_unlock(&data->meal_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->meal_mutex);
	}
	return (false);
}

static bool	check_meals_complete(t_data *data)
{
	int	i;

	if (data->max_meals == -1LL) // Явное указание типа
		return (false);
	for (i = 0; i < data->num_philos; i++)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if ((int64_t)data->philos[i].meals_eaten < data->max_meals)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (false);
		}
		pthread_mutex_unlock(&data->meal_mutex);
	}
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_simulation_end(philo->data))
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, FORK_TAKEN);
		print_status(philo, EATING);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->last_meal = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		print_status(philo, SLEEPING);
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, THINKING);
	}
	return (NULL);
}

void	monitor_simulation(t_data *data)
{
	while (!check_simulation_end(data))
	{
		usleep(1000);
		if (check_philo_death(data) || check_meals_complete(data))
			break ;
	}
}
