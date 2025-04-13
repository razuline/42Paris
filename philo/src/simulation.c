/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/05 11:26:43 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	should_continue(t_data *data)
{
	return !(data->someone_died || data->philos_ate_enough);
}

void	philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (should_continue(philo->data))
	{
		take_forks(philo);
		philo_eat(philo);
		put_forks(philo);
		usleep(100);
		philo_sleep(philo);
		usleep(100);
		philo_think(philo);
		usleep(100);
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
		monitor(data);
		i = -1;
		while (++i < data->number_of_philosophers)
			pthread_join(&data->philos[i].philo_thread, NULL);
		return (SUCCESS);
	}
}
