/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:38:02 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/13 12:43:31 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialise_simulation(t_data *data, int ac, char **av)
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

int	handle_single_philo(t_data *data)
{
	pthread_mutex_lock(&data->forks[0]);
	print_status(&data->philos[0], FORK_TAKEN);
	precise_usleep(data->time_to_die, data);
	pthread_mutex_lock(&data->stop_mutex);
	if (!data->stop_flag)
	{
		data->stop_flag = true;
		print_status(&data->philos[0], "died");
	}
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_unlock(&data->forks[0]);
	return (SUCCESS);
}

static void	run_multi_philo_simulation(t_data *data)
{
	if (start_simulation(data) != SUCCESS)
		return ;
	monitor_simulation(data);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = -1;
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

int	main(int ac, char **av)
{
	t_data	data;
	int		status;

	status = initialise_simulation(&data, ac, av);
	if (status != SUCCESS)
		return (status);
	if (data.num_philos == 1)
		status = handle_single_philo(&data);
	else
		run_multi_philo_simulation(&data);
	cleanup(&data);
	return (status);
}
