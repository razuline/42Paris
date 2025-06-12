/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/12 22:47:10 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			error_exit(data, "Error: Thread creation failed", ERR_THREAD);
			return ;
		}
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av) != SUCCESS)
		return (1);
	if (init_resources(&data) != SUCCESS)
		return (cleanup(&data), 1);
	if (data.num_philos == 1)
	{
		pthread_mutex_lock(&data.forks[0]);
		print_status(&data.philos[0], FORK_TAKEN);
		precise_usleep(data.time_to_die, &data);
		pthread_mutex_lock(&data.stop_mutex);
		if (!data.stop_flag)
		{
			data.stop_flag = true;
			print_status(&data.philos[0], DIED);
		}
		pthread_mutex_unlock(&data.stop_mutex);
		pthread_mutex_unlock(&data.forks[0]);
		cleanup(&data);
		return (0);
	}
}
