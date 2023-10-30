/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:31:24 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 17:00:27 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_prog *prog, int nb_of_philo)
{
	pthread_t	watcher;
	int	i;

	i = 0;
	printf("////////%d//////////\n", nb_of_philo);
	if (pthread_create(&watcher, NULL, &monitor, prog->philo) != 0)
		return(1);
	while(i < nb_of_philo)
	{
		if (pthread_create(&prog->philo[i].thread, NULL, &philo_routine, &prog->philo[i]) != 0)
			return(1);
		i++;
	}
	if (pthread_join(watcher, NULL) != 0)
		return (1);
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(prog->philo[i].thread, NULL) != 0)
			return(1);
		i++;
	}
	return (0);
}