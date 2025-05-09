/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:20:53 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 10:38:28 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_sleep(uint64_t ms)
{
	uint64_t	start;
	uint64_t	remaining;

	start = get_time();
	remaining = ms;
	while (remaining > 10)
	{
		usleep(remaining * 900);
		remaining = ms - (get_time() - start);
	}
	while (get_time() - start < ms)
		usleep(100);
}
