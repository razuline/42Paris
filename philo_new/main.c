/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/14 16:14:37 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_simulation(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av) != SUCCESS)
		return (FAILURE);
	if (init_resources(data) != SUCCESS)
	{
		cleanup(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			error_exit(data, "Error: Thread creation failed", ERR_THREAD);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	single_philo_case(t_data *data)
{
	data->start_time = get_time();
	pthread_mutex_lock(&data->forks[0]);
	print_status(&data->philos[0], FORK_TAKEN);
	precise_usleep(data->time_to_die, data);
	pthread_mutex_lock(&data->stop_mutex);
	data->stop_flag = true;
	pthread_mutex_unlock(&data->stop_mutex);
	print_status(&data->philos[0], DIED);
	pthread_mutex_unlock(&data->forks[0]);
	return (SUCCESS);
}

static void	multi_philo_case(t_data *data)
{
	if (start_simulation(data) != SUCCESS)
		return ;
	monitor(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (init_simulation(&data, ac, av) != SUCCESS)
		return (1);
	if (data.num_philos == 1)
		single_philo_case(&data);
	else
		multi_philo_case(&data);
	cleanup(&data);
	return (0);
}
