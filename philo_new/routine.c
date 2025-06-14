/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:48:40 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 18:14:33 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	make_single_cycle(t_philo *philo)
{
	take_forks(philo);
	if (is_simulation_stopped(philo->data))
	{
		put_forks(philo);
		return (false);
	}
	philo_eat(philo);
	put_forks(philo);
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
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_barrier_wait(&philo->data->barrier);
	if (philo->id % 2 == 0)
		precise_usleep(1, philo->data);
	while (make_single_cycle(philo) && !is_simulation_stopped(philo->data))
		;
	return (NULL);
}
