/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:56:08 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/07 14:25:41 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo, FORK_TAKEN);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo, FORK_TAKEN);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	print_status(philo, EATING);
	precise_usleep(philo->data->time_to_eat);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

static void	sleep_and_think(t_philo *philo)
{
	print_status(philo, SLEEPING);
	precise_usleep(philo->data->time_to_sleep);
	print_status(philo, THINKING);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
