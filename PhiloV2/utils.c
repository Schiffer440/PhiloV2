/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:24:35 by adugain           #+#    #+#             */
/*   Updated: 2023/11/03 16:17:16 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[1]) > 200)
			return (1);
		if (ft_atol(av[i]) <= 0 || ft_atol(av[i]) > INT_MAX)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atol(const char *str)
{
	int		i;
	long	nb;
	long	sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		sign = -sign;
		i++;
	}
	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	print_message(char *str, t_philo *philo, int index)
{
	uint64_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->prog->start_time;
	if (check_vitals(philo) == 0)
		printf("%ld %d %s\n", time, index, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	ft_usleep(uint64_t time, t_philo *philo)
{
	uint64_t	begin;
	uint64_t	now;

	now = get_time();
	begin = now;
	while (now - begin < time)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead == 1)
		{
			pthread_mutex_unlock(philo->dead_lock);
			return ;
		}
		pthread_mutex_unlock(philo->dead_lock);
		usleep(1000);
		now = get_time();
	}
}
