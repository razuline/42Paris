/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:19:27 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 16:19:19 by erazumov         ###   ########.fr       */
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

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	precise_usleep(long ms, t_data *data)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_time();
	while (1)
	{
		elapsed_time = get_time() - start_time;
		if (elapsed_time >= ms)
			break ;
		if (is_simulation_stopped(data))
			return ;
		usleep(500);
	}
}
