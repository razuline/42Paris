/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:30:30 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 19:22:53 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo);
static void	drop_forks(t_philo *philo);

void	philo_eats(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	print_status(philo, EATING, false);
	pthread_mutex_unlock(&philo->philo_lock);
	precise_usleep(philo->data->time_to_eat, philo->data);
	drop_forks(philo);
}

void	philo_sleeps(t_philo *philo)
{
	print_status(philo, SLEEPING, true);
	precise_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_thinks(t_philo *philo)
{
	print_status(philo, THINKING, true);
	usleep(100);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN, true);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN, true);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, FORK_TAKEN, true);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, FORK_TAKEN, true);
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}
