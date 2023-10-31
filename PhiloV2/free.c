/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:46:54 by adugain           #+#    #+#             */
/*   Updated: 2023/10/31 16:09:06 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_prog *prog)
{
	free(prog->forks);
	free(prog->philo);
}

void	free_mutex(t_prog *prog)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&prog->eat_lock);
	pthread_mutex_destroy(&prog->write_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	while (i < prog->nb_of_philo)
	{
		pthread_mutex_destroy(&prog->forks[i]);
		i++;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (1);
	while (i < n && (u1[i] != '\0' || u2[i] != '\0'))
	{
		if (u1[i] != u2[i] && (u1[i] != '\0' || u2[i] != '\0'))
			return (u1[i] - u2[i]);
		else
			i++;
	}
	return (0);
}
