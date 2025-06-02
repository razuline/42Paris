/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:00:33 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 17:00:55 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;

	if (data->num_philos == 1)
		return (one_philo_case(philo), NULL);

	while (1)
	{
		take_forks(philo);

		eat(philo);

		drop_forks(philo);

		print_status(philo, SLEEPING);
		ft_usleep(data->time_to_sleep);

		print_status(philo, THINKING);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_status(philo, FORK_TAKEN);

	pthread_mutex_lock(&data->forks[philo->right_fork]);
	print_status(philo, FORK_TAKEN);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, EATING);

	pthread_mutex_lock(&data->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_mutex);

	ft_usleep(data->time_to_eat);
}

void	drop_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}

void	one_philo_case(t_philo *philo)
{
	print_status(philo, FORK_TAKEN);
	ft_usleep(philo->data->time_to_die);
	print_status(philo, DIED);
}
