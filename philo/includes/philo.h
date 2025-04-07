/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/04/07 16:21:27 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define ERROR 1

/* Philos' messages*/
# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				meals_eaten;
	uint64_t		last_meal_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				number_of_philosophers;
	uint64_t		start_time;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	int				must_eat_count;
	int				someone_died;
	int				philos_ate_enough;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
}			t_data;

/* Initialisation */
int			init_data(t_data *data, int ac, char **av);
int			init_mutexes(t_data *data);
int			init_philos(t_data *data);

/* Time (+ test) */
uint64_t	get_time(void);
void		ft_sleep(uint64_t ms);

/* Actions */
void		take_forks(t_philo *philo);
void		put_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);

/* Simulation */
int			should_continue(t_data *data);
void		*philo_routine(void *arg);
int			simulation_start(t_data *data);

/* Monitor */
void		monitor(t_data *data);
int			alloc_resources(t_data *data);

/* Utils (+ test_atoi) */
void		print_status(t_philo *philo, char *status);
long		ft_atoi(const char *str);
void		clear_data(t_data *data);

#endif
