/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:52:25 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 19:07:40 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *philo_ptr);
static void	*monitor(void *data_ptr);
static bool	check_stop_condition(t_data *data);
static bool	philo_is_dead(t_philo *philo);

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = get_time();
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_lock);
		data->philos[i].last_meal_time = data->start_time;
		pthread_mutex_unlock(&data->philos[i].philo_lock);
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			return (printf("Error: Failed to create a philo thread.\n"), 1);
	}
	if (pthread_create(&monitor_thread, NULL, &monitor, data) != 0)
		return (printf("Error: Failed to create monitor thread.\n"), 1);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

static void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	if (philo->data->num_philos == 1)
	{
		print_status(philo, FORK_TAKEN, true);
		precise_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (simulation_end(philo->data))
	{
		philo_eats(philo);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}

static void	*monitor(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	while (1)
	{
		if (check_stop_condition(data))
			break ;
		usleep(500);
	}
	return (NULL);
}

static bool	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	if ((get_time() - philo->last_meal_time) > philo->data->time_to_die)
	{
		print_status(philo, DIED, true);
		pthread_mutex_lock(&philo->data->stop_lock);
		philo->data->simulation_end = true;
		pthread_mutex_unlock(&philo->data->stop_lock);
		pthread_mutex_unlock(&philo->philo_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->philo_lock);
	return (false);
}

static bool	check_stop_condition(t_data *data)
{
	int	i;
	int	finished_eating;

	finished_eating = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		if (philo_is_dead(&data->philos[i]))
			return (true);
		pthread_mutex_lock(&data->philos[i].philo_lock);
		if (data->num_must_eat != -1
			&& data->philos[i].eat_count >= data->num_must_eat)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].philo_lock);
	}
	if (data->num_must_eat != -1 && finished_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->stop_lock);
		return (true);
	}
	return (false);
}
