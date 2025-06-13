/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/13 12:52:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, FORK_TAKEN);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, FORK_TAKEN);
	}
}

static void	put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
}

static void	eat(t_philo *philo)
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
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(5, philo->data);
	while (!is_simulation_stopped(philo->data))
	{
		take_forks(philo);
		eat(philo);
		put_forks(philo);
		print_status(philo, SLEEPING);
		precise_usleep(philo->data->time_to_sleep, philo->data);
		print_status(philo, THINKING);
	}
	return (NULL);
}
