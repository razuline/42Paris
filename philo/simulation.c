/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:52:25 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 21:45:19 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *philo_ptr);
static void	*monitor(void *data_ptr);
static bool	check_philo_died(t_philo *philo);
static bool	check_all_ate(t_data *data);

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
			return (printf("Error: Failed to create philo thread.\n"), 1);
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
		print_status(philo, FORK_TAKEN);
		precise_usleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!simulation_end(philo->data))
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
	while (true)
	{
		if (check_philo_died(data->philos) || check_all_ate(data))
			break ;
		usleep(500);
	}
	return (NULL);
}

static bool	check_philo_died(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_philos)
	{
		pthread_mutex_lock(&philos[i].philo_lock);
		if ((get_time() - philos[i].last_meal_time) > philos->data->time_to_die)
		{
			pthread_mutex_unlock(&philos[i].philo_lock);
			print_status(&philos[i], DIED);
			pthread_mutex_lock(&philos->data->stop_lock);
			philos->data->simulation_end = true;
			pthread_mutex_unlock(&philos->data->stop_lock);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].philo_lock);
	}
	return (false);
}

static bool	check_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->nbr_must_eat == -1)
		return (false);
	finished_eating = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].philo_lock);
		if (data->philos[i].eat_count >= data->nbr_must_eat)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].philo_lock);
	}
	if (finished_eating == data->num_philos)
	{
		pthread_mutex_lock(&data->stop_lock);
		data->simulation_end = true;
		pthread_mutex_unlock(&data->stop_lock);
		return (true);
	}
	return (false);
}
