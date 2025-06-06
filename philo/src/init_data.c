/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:25:00 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/06 18:04:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_args(t_data *data, int ac, char **av)
{
	if (safe_atoi(av[1], &data->num_philos) != SUCCESS
		|| data->num_philos <= 0)
		return (error_exit(data, "Error: Invalid philosopher count", ERR_ARGS));
	if (safe_atoi(av[2], &data->time_to_die) != SUCCESS
		|| data->time_to_die <= 0)
		return (error_exit(data, "Error: Invalid time_to_die", ERR_ARGS));
	if (safe_atoi(av[3], &data->time_to_eat) != SUCCESS
		|| data->time_to_eat <= 0)
		return (error_exit(data, "Error: Invalid time_to_eat", ERR_ARGS));
	if (safe_atoi(av[4], &data->time_to_sleep) != SUCCESS
		|| data->time_to_sleep <= 0)
		return (error_exit(data, "Error: Invalid time_to_sleep", ERR_ARGS));
	if (ac == 6 && (safe_atoi(av[5], &data->max_meals) != SUCCESS
			|| data->max_meals <= 0))
		return (error_exit(data, "Error: Invalid max_meals", ERR_ARGS));
	return (SUCCESS);
}

int	init_data(t_data *data, int ac, char **av)
{
	memset(data, 0, sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (error_exit(data,
				"Usage: ./philo n_philo t_die t_eat t_sleep [max_meals]",
				ERR_ARGS));
	if (parse_args(data, ac, av) != SUCCESS)
		return (FAILURE);
	data->start_time = get_time();
	data->stop_flag = false;
	return (SUCCESS);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philos[i].thread);
		i++;
	}
	free(data->forks);
	free(data->philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
}

int	error_exit(t_data *data, const char *msg, t_error err)
{
	pthread_mutex_lock(&data->print_mutex);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	pthread_mutex_unlock(&data->print_mutex);
	return ((int)err);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
