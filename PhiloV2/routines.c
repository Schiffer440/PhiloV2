/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:01:25 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 16:54:14 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_vitals(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return(pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (check_vitals(philo) == 0)
	{
		// printf("**************\n");
		// usleep(1);
		eat_r(philo);
		// usleep(1);
		sleep_r(philo);
		// usleep(1);
		think_r(philo);
		// printf("+++++++++++++++++\n");
	}
	return (arg);
}

void	think_r(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
	usleep(philo->time_to_think * 1000);
}

void	sleep_r(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	usleep(philo->time_to_sleep * 1000);
}

void	eat_r(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->l_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat_lock);
	philo->eat_count++;
	philo->last_meal = get_time() - philo->prog->start_time;
	pthread_mutex_unlock(philo->eat_lock);
	usleep(philo->time_to_eat * 1000);
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	// print_message("has dropped a fork", philo, philo->id);
	pthread_mutex_unlock(philo->l_fork);
	// print_message("has dropped a fork", philo, philo->id);

}