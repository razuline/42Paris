/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:37:42 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 21:42:32 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	if (data->forks)
	{
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	i = -1;
	if (data->philos)
	{
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->philos[i].philo_lock);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->stop_lock);
}
