/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:40:18 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/07 14:22:26 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1

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
	long			last_meal;
	int				left_fork;
	int				right_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				max_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	stop_mutex;
	bool			stop_flag;
	t_philo			*philos;
}					t_data;

typedef enum e_error
{
	ERR_ARGS = 1,
	ERR_MALLOC,
	ERR_MUTEX,
	ERR_THREAD,
}					t_error;

/* Initialisation */
int					init_data(t_data *data, int ac, char **av);
int					init_resources(t_data *data);

/* Threads */
void				*philo_routine(void *arg);
void				monitor_simulation(t_data *data);
void				start_simulation(t_data *data);

/* Utils */
int					parse_time_value(const char *str, long *time);
long				get_time(void);
void				precise_usleep(long ms);
int					safe_atoi(const char *str, int *num);
void				print_status(t_philo *philo, char *msg);

/* Clean up */
void				cleanup(t_data *data);
int					error_exit(t_data *data, const char *msg, t_error err);
size_t				ft_strlen(const char *s);

#endif
