/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:17:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 18:16:24 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all_resources(t_data *data)
{
	int	i;

	i = -1;
	while (data->forks && ++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	i = -1;
	while (data->philos && ++i < data->num_philos)
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_barrier_destroy(&data->barrier);
}

void	cleanup(t_data *data)
{
	int	i;

	i = -1;
	while (data->philos && ++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	destroy_all_resources(data);
}
