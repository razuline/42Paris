/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/03 15:07:46 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* Philos' messages*/
# define FORK_TAKEN "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	uint64_t		last_meal_time;
	int				left_fork;
	int				right_fork;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
	int				is_dead;
}			t_data;

typedef enum e_errors
{
	SUCCESS = 0,
	ERR_ARG_COUNT,
	ERR_ARGS_INVALID,
	ERR_MALLOC,
	ERR_MUTEX_INIT,
	ERR_THREAD_CREATE,
	ERR_THREAD_JOIN,
	ERR_SIMULATION,
	ERR_TIME
}			t_errors;

/* Initialisation */
t_errors	init_data(t_data *data, int ac, char **av);
int			init_forks(t_data *data);
int			init_philos(t_data *data);

/* Simulations */
int		start_simulation(t_data *data);
void	monitor_simulation(t_data *data);

/* Actions */
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
void	eat(t_philo *philo);
void	one_philo_case(t_philo *philo);

/* Utils */
void		clear_data(t_data *data);
uint64_t	get_time_in_ms(void);
void		ft_usleep(long ms);
void		print_status(t_philo *philo, char *msg);
int			safe_atoi(char *str, int *result); /* (+ test) */

#endif
