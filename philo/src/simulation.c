/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:56:03 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/02 15:42:38 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	should_continue(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->meal_mutex);
	result = !data->is_dead && !data->philos_ate_enough;
	pthread_mutex_unlock(&data->meal_mutex);
	return (result);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (should_continue(philo->data))
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine,
				&data->philos[i]) != 0)
			return (printf("Error: Thread creation failed\n"), FAILURE);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_detach(data->philos[i].thread) != 0)
			return (printf("Error: Thread detach failed\n"), FAILURE);
		i++;
	}
	return (SUCCESS);

}
