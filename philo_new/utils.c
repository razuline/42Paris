/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:10:31 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 16:53:39 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_atoi(const char *str, int *num)
{
	int			sign;
	long long	result;

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
		if ((sign == 1 && result > INT_MAX) || (sign == -1 && result >
				-(long)INT_MIN))
			return (FAILURE);
	}
	*num = (int)(result * sign);
	return (SUCCESS);
}

bool	is_simulation_stopped(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->stop_mutex);
	ret = data->stop_flag;
	pthread_mutex_unlock(&data->stop_mutex);
	return (ret);
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (strcmp(status, DIED) == 0)
	{
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			status);
	}
	else if (!is_simulation_stopped(philo->data))
	{
		printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id,
			status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
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
