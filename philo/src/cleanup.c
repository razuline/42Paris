/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 13:17:05 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/12 22:26:51 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (!data)
		return ;
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_mutex);
	i = -1;
	while (data->philos && ++i < data->num_philos)
	{
		if (data->philos[i].thread)
			pthread_join(data->philos[i].thread, NULL);
	}
	i = -1;
	while (data->forks && ++i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	error_exit(t_data *data, const char *msg, t_error err)
{
	if (data)
		pthread_mutex_lock(&data->print_mutex);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (data)
		pthread_mutex_unlock(&data->print_mutex);
	return ((int)err);
}
