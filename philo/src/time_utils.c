/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:19:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/13 12:25:20 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_time_value(const char *str, long *time)
{
	int	tmp;

	if (safe_atoi(str, &tmp) != SUCCESS || tmp < 0)
		return (FAILURE);
	*time = (long)tmp;
	return (SUCCESS);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long ms, t_data *data)
{
	long	start_time;
	long	end_time;

	start_time = get_time();
	end_time = start_time + ms;
	while (get_time() < end_time)
	{
		if (data && is_simulation_stopped(data))
			return ;
		usleep(100);
	}
}
