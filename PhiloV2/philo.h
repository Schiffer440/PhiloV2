/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:55:42 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 16:59:41 by adugain          ###   ########.fr       */
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

struct s_prog;

typedef struct s_philo
{
	struct s_prog	*prog;
	pthread_t	thread;
	int		id;
	int		eat_count;
	int		eating;
	int		*dead;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	time_to_think;
	uint64_t	last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
}t_philo;


typedef struct s_prog
{
	int		nb_of_philo;
	t_philo	*philo;
	uint64_t	start_time;
	uint64_t	death_time;
	int		dead;
	int		meal_needed;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;	
}t_prog;

int	ft_atoi(const char *str);
int	init_prog(t_prog *prog, char **av);
int	init_philo_fork(t_prog *prog, t_philo *philo, char **av);
uint64_t	get_time(void);
int	check_args(char **av);
int	philosophers(t_prog *prog, int nb_of_philo);
void	print_message(char *str, t_philo *philo, int index);
void	*monitor(void*arg);
void	*philo_routine(void *arg);
int	check_vitals(t_philo *philo);
void	think_r(t_philo *philo);
void	sleep_r(t_philo *philo);
void	eat_r(t_philo *philo);

#endif