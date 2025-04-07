/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 16:03:54 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	should_continue(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->meal_mutex);
	result = !data->someone_died && !data->philos_ate_enough;
	pthread_mutex_unlock(&data->meal_mutex);
	return (result);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		usleep(1000);
	while (should_continue(philo->data))
	{
		take_forks(philo);
		philo_eat(philo);
		put_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	simulation_start(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (ERROR);
	}
	monitor(data);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(data->philos[i].philo_thread, NULL);
	return (SUCCESS);
}
