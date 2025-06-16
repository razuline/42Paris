/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:26:43 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 19:17:35 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_philos(t_data *data);
static int	init_mutexes(t_data *data);
static int	validate_args(t_data *data, int ac);

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_must_eat = ft_atoi(av[5]);
	else
		data->num_must_eat = -1;
	if (validate_args(data, ac) != 0)
		return (1);
	data->simulation_end = false;
	data->philos = NULL;
	data->forks = NULL;
	if (init_mutexes(data) != 0)
		return (1);
	if (init_philos(data) != 0)
	{
		cleanup(data);
		return (1);
	}
	return (0);
}

static int	validate_args(t_data *data, int ac)
{
	if (data->num_philos <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (ac == 6 && data->num_must_eat <= 0))
	{
		printf("Erreur: Valeurs d'arguments invalides.\n");
		return (1);
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (printf("Erreur: Malloc a échoué pour les fourchettes.\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (printf("Erreur: L'init du mutex de fourchette a échoué.\n"),
				1);
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0
		|| pthread_mutex_init(&data->stop_lock, NULL) != 0)
		return (printf("Erreur: L'init du mutex général a échoué.\n"), 1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("Erreur: Malloc a échoué pour les philosophes.\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		if (pthread_mutex_init(&data->philos[i].philo_lock, NULL) != 0)
			return (printf("Erreur: L'init du mutex de philosophe a échoué.\n"),
				1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
