/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erazumov <erazumov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:30:10 by erazumov          #+#    #+#             */
/*   Updated: 2025/06/16 21:41:29 by erazumov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* Philosopher status messages */
# define FORK_TAKEN "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					eat_count;
	long long			last_meal_time;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		philo_lock;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					nbr_must_eat;
	bool				simulation_end;
	long long			start_time;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		stop_lock;
}						t_data;

/* init.c */
int						init_data(t_data *data, int argc, char **argv);
int						ft_strcmp(const char *s1, const char *s2);

/* simulation.c */
int						start_simulation(t_data *data);

/* actions.c */
void					philo_eats(t_philo *philo);
void					philo_sleeps(t_philo *philo);
void					philo_thinks(t_philo *philo);

/* utils.c */
int						ft_atoi(const char *str);
long long				get_time(void);
void					precise_usleep(long long ms, t_data *data);
void					print_status(t_philo *philo, char *status);
bool					simulation_end(t_data *data);

/* cleanup.c */
void					cleanup(t_data *data);

#endif
