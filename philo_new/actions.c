/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:35:48 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 18:05:59 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	take_single_fork(t_philo *philo, int fork_idx)
{
	pthread_mutex_lock(&philo->data->forks[fork_idx]);
	print_status(philo, FORK_TAKEN);
	if (is_simulation_stopped(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[fork_idx]);
		return (false);
	}
	return (true);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (!take_single_fork(philo, philo->right_fork))
			return ;
		precise_usleep(1, philo->data);
		if (!take_single_fork(philo, philo->left_fork))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			return ;
		}
	}
	else
	{
		if (!take_single_fork(philo, philo->left_fork))
			return ;
		precise_usleep(1, philo->data);
		if (!take_single_fork(philo, philo->right_fork))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			return ;
		}
	}
}

void	put_forks(t_philo *philo)
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, EATING);
	precise_usleep(philo->data->time_to_eat, philo->data);
	philo->meals_eaten++;
	if (philo->data->max_meals != -1
		&& philo->meals_eaten == philo->data->max_meals)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->data->philos_ate_enough++;
		pthread_mutex_unlock(&philo->data->meal_mutex);
	}
}
