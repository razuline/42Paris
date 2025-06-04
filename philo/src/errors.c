/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:50:44 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/04 17:02:58 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_errors	print_error(const char *msg, t_errors err_code)
{
	pthread_mutex_lock(&g_error_mutex);
	printf("%s", msg);
	if (err_code == ERR_MALLOC)
		printf("Details: %s\n", strerror(errno));
	pthread_mutex_unlock(&g_error_mutex);
	return (err_code);
}

t_errors	verify_simulation(t_data *data)
{
	if (data->num_philos > MAX_PHILOS)
		return (print_error("Error: Too many philosophers\n",
				ERR_ARGS_INVALID));
	if (data->time_to_die < data->time_to_eat + data->time_to_sleep)
		print_error("Warning: Philosophers may die frequently\n", SUCCESS);
	return (SUCCESS);
}
