/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/07 16:25:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_simulation_stopped(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, FORK_TAKEN);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static bool	perform_philo_actions(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, EATING);
	precise_usleep(philo->data->time_to_eat);
	if (is_simulation_stopped(philo->data))
		return (false);
	print_status(philo, SLEEPING);
	precise_usleep(philo->data->time_to_sleep);
	if (is_simulation_stopped(philo->data))
		return (false);
	print_status(philo, THINKING);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (data->num_philos == 1)
	{
		print_status(philo, FORK_TAKEN);
		precise_usleep(data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(1000);
	while (!is_simulation_stopped(data))
	{
		take_forks(philo);
		if (is_simulation_stopped(data) || !perform_philo_actions(philo))
		{
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
	}
	return (NULL);
}
