/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:10:41 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 21:46:05 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_usleep(long long ms, t_data *data)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (simulation_end(data))
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!simulation_end(philo->data) || ft_strcmp(status, DIED) == 0)
	{
		printf("%lld %d %s\n", get_time() - philo->data->start_time, philo->id,
			status);
	}
	pthread_mutex_unlock(&philo->data->print_lock);
}

bool	simulation_end(t_data *data)
{
	bool	ended;

	pthread_mutex_lock(&data->stop_lock);
	ended = data->simulation_end;
	pthread_mutex_unlock(&data->stop_lock);
	return (ended);
}
