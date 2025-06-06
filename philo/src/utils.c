/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:10:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/06 15:49:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(uint64_t ms)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

int	safe_atoi(const char *str, int *num)
{
	int			sign;
	uint64_t	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		if ((sign == 1 && result > INT_MAX) || (sign == -1
				&& result > (uint64_t)INT_MAX + 1))
			return (ERR_ARGS);
	}
	*num = (int)(result * sign);
	return (SUCCESS);
}

void	print_status(t_philo *philo, char *msg)
{
	t_data		*data;
	uint64_t	timestamp;

	data = philo->data;
	timestamp = get_time() - data->start_time;
	pthread_mutex_lock(&data->print_mutex);
	if (!check_simulation_stop(data))
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&data->print_mutex);
}

static void	set_simulation_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_mutex);
}
