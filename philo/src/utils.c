/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:10:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 16:45:49 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i]);
	i++;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);

	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	uint64_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *msg)
{
	t_data		*data;
	uint64_t	curr_time;

	data = philo->data;
	curr_time = get_time_in_ms() - data->start_time;

	pthread_mutex_lock(&data->print_mutex);

	if (!data->is_dead)
		printf(msg, curr_time, philo->id);

	pthread_mutex_unlock(&data->print_mutex);
}

long	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}
