/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:45:45 by adugain           #+#    #+#             */
/*   Updated: 2023/10/31 16:02:33 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_philo *philo)
{
	uint64_t	time;

	time = get_time() - philo->prog->start_time;
	pthread_mutex_lock(philo->eat_lock);
	if ((time - philo->last_meal) >= \
	philo->prog->death_time && philo->eating == 0)
		return (pthread_mutex_unlock(philo->eat_lock), 1);
	pthread_mutex_unlock(philo->eat_lock);
	return (0);
}

int	check_vitals(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

int	dead_check(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->prog->nb_of_philo)
	{
		if (is_dead(philo))
		{
			print_message("just died !!!\n", &philo[i], philo[i].id);
			pthread_mutex_lock(&philo->prog->dead_lock);
			*philo->dead = 1;
			pthread_mutex_unlock(&philo->prog->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	are_full(t_philo *philo)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < philo->prog->nb_of_philo)
	{
		pthread_mutex_lock(&philo->prog->eat_lock);
		if (philo[i].eat_count == philo->prog->meal_needed)
			finished++;
		pthread_mutex_unlock(&philo->prog->eat_lock);
		i++;
	}
	if (finished >= philo->prog->nb_of_philo)
	{
		pthread_mutex_lock(&philo->prog->dead_lock);
			*philo->dead = 1;
		pthread_mutex_unlock(&philo->prog->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_prog	*prog;
	int		i;

	i = 0;
	prog = (t_prog *)arg;
	while (i < 5)
	{
		if (dead_check(prog->philo) == 1 || are_full(prog->philo) == 1)
			break ;
	}
	return (arg);
}
