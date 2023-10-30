/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:18:53 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 16:24:36 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_prog(t_prog *prog, char **av)
{
	prog->nb_of_philo = ft_atoi(av[1]);
	prog->philo = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	prog->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!prog->philo || !prog->forks)
		return (1);
	prog->death_time = ft_atoi(av[2]);
	if (av[5])
		prog->meal_needed = ft_atoi(av[5]);
	else
		prog->meal_needed = -1;
	prog->dead = 0;
	prog->start_time = get_time();
	if (pthread_mutex_init(&prog->eat_lock, NULL) != 0 
		|| pthread_mutex_init(&prog->dead_lock, NULL) != 0
		|| pthread_mutex_init(&prog->write_lock, NULL) != 0)
	{
		free(prog->philo);
		return(1);
	}
	return(0);
}

int	init_philo_fork(t_prog *prog, t_philo *philo, char **av)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philo[i].dead_lock = &prog->dead_lock;
		philo[i].eat_lock = &prog->eat_lock;
		philo[i].write_lock = &prog->write_lock;
		philo[i].time_to_eat = ft_atoi(av[3]);
		philo[i].time_to_sleep = ft_atoi(av[4]);
		philo[i].time_to_think = ft_atoi(av[4]) / 2;
		philo[i].prog = prog;
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].eating = 0;
		philo[i].dead = &prog->dead;
		philo[i].last_meal = 0;
		philo[i].l_fork = philo[i].prog->forks;
		if (i == 0)
			philo[i].r_fork = &philo[i].prog->forks[ft_atoi(av[1]) - 1];
		else
			philo[i].r_fork = &philo[i].prog->forks[i - 1];
			
		i++;
	}
	return (0);
}
