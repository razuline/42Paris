/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 19:06:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->philos[i].philo_lock);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->stop_lock);
}
