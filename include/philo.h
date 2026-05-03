/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalguer <asalguer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:56:41 by asalguer          #+#    #+#             */
/*   Updated: 2025/10/17 17:57:03 by asalguer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

/************ Instructions ************/
void					instructions(void);

/************** Structs ***************/

typedef struct s_philo	t_philo;

/* Rules Struct */
typedef struct s_rules
{
	int					n_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	long				start_time;
	int					threads_ready;
	int					stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		data_mutex;
	pthread_t			monitor;
	t_philo				*philo;
}						t_rules;

/* Philosopher Struct */
typedef struct s_philo
{
	pthread_t			thrd;
	int					id;
	int					times_eaten;
	long				last_meal;
	int					dead;
	int					eating;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		philo_mutex;
	t_rules				*rules;
}						t_philo;

/************** Functions *************/
/* Philo */
void					*death_checker(void *args);
void					init_routine(t_rules *rules);
void					*routine(void *args);
void					*death_checker(void *args);
void					*death_checker_utils(t_philo *philo, t_rules *rules,
							long *last_meal, long *current);
void					clean_all(t_rules *rules);

/* Utils Data */
int						args_check(int argc, char **argv);
void					*smalloc(size_t bytes);
void					*init_data(char **argv, t_rules *rules);

/* Utils Functions */
int						ft_atoi(char *str);
long					get_time(void);
void					ft_sleep(t_philo *philo, int ms);
void					safe_print(t_philo *philo, int id, const char *msg);
long					timestamp_ms(long start);

#endif