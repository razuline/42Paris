/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/12 22:48:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_simulation_stopped(t_data *data)
{
	bool	stop;

	pthread_mutex_lock(&data->stop_mutex);
	stop = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (stop);
}

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->left_fork < philo->right_fork)
	{
		first_fork = &philo->data->forks[philo->left_fork];
		second_fork = &philo->data->forks[philo->right_fork];
	}
	else
	{
		first_fork = &philo->data->forks[philo->right_fork];
		second_fork = &philo->data->forks[philo->left_fork];
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, FORK_TAKEN);
	if (is_simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_status(philo, FORK_TAKEN);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static bool	perform_philo_actions(t_philo *philo)
{
	print_status(philo, EATING);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	if (philo->data->max_meals != -1
		&& philo->meals_eaten >= philo->data->max_meals)
		philo->data->philos_ate_enough++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	precise_usleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
	if (is_simulation_stopped(philo->data))
		return (false);
	print_status(philo, SLEEPING);
	precise_usleep(philo->data->time_to_sleep, philo->data);
	if (is_simulation_stopped(philo->data))
		return (false);
	print_status(philo, THINKING);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		if (is_simulation_stopped(philo->data))
		{
			drop_forks(philo);
			break ;
		}
		print_status(philo, EATING);
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->last_meal = get_time();
		philo->meals_eaten++;
		if (philo->data->max_meals != -1
			&& philo->meals_eaten >= philo->data->max_meals)
			philo->data->philos_ate_enough++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
		precise_usleep(philo->data->time_to_eat, philo->data);
		drop_forks(philo);
		if (is_simulation_stopped(philo->data))
			break ;
		print_status(philo, SLEEPING);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		if (is_simulation_stopped(philo->data))
			break ;
		print_status(philo, THINKING);
	}
	return (NULL);
}
