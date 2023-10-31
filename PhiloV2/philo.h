/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:55:42 by adugain           #+#    #+#             */
/*   Updated: 2023/10/31 16:12:08 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

struct	s_prog;

typedef struct s_philo
{
	struct s_prog	*prog;
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				eating;
	int				*dead;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_think;
	uint64_t		last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}t_philo;

typedef struct s_prog
{
	t_philo			*philo;
	pthread_t		watcher;
	int				nb_of_philo;
	int				dead;
	int				meal_needed;
	uint64_t		start_time;
	uint64_t		death_time;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;	
}t_prog;

uint64_t	get_time(void);
int			ft_atoi(const char *str);
int			init_prog(t_prog *prog, char **av);
int			init_philo_fork(t_prog *prog, t_philo *philo, char **av);
int			check_args(char **av);
int			philosophers(t_prog *prog, int nb_of_philo);
int			check_vitals(t_philo *philo);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		print_message(char *str, t_philo *philo, int index);
void		*monitor(void*arg);
void		*philo_routine(void *arg);
void		think_r(t_philo *philo);
void		sleep_r(t_philo *philo);
void		eat_r(t_philo *philo);
void		eat_l(t_philo *philo);
void		free_mutex(t_prog *prog);
void		ft_usleep(uint64_t time, t_philo *philo);
void		free_memory(t_prog *prog);

#endif