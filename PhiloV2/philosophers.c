/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:31:24 by adugain           #+#    #+#             */
/*   Updated: 2023/11/03 17:08:09 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers(t_prog *prog, int nb_of_philo)
{
	int	i;

	i = 0;
	if (pthread_create(&prog->watcher, NULL, &monitor, prog) != 0)
		return (1);
	while (i < nb_of_philo)
	{
		if (pthread_create(&prog->philo[i].thread, \
		NULL, &philo_routine, &prog->philo[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_join(prog->watcher, NULL) != 0)
		return (1);
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_join(prog->philo[i].thread, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
