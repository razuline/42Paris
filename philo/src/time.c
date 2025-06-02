/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:20:53 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 15:22:00 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(uint64_t ms)
{
	uint64_t	start;
	uint64_t	remaining;

	start = get_time_in_ms();
	remaining = ms;
	while (remaining > 10)
	{
		usleep(remaining * 900);
		remaining = ms - (get_time_in_ms() - start);
	}
	while (get_time_in_ms() - start < ms)
		usleep(100);
}
