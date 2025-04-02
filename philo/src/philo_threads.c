/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/02 15:27:17 by erazumov         ###   ########.fr       */
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
