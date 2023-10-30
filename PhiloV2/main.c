/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adugain <adugain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:04:44 by adugain           #+#    #+#             */
/*   Updated: 2023/10/30 16:58:05 by adugain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
int	main(int ac, char **av)
{
	t_prog	prog;
	
	if (ac == 6 || ac == 5)
	{
		if (check_args(av) != 0)
			return (printf("Wrong args...\n"));
		if (init_prog(&prog, av) != 0)
			return (printf("Prog init error...\n"));
		if (init_philo_fork(&prog, prog.philo, av) != 0)
			return (printf("Philo or fork init error...\n"));
		philosophers(&prog, ft_atoi(av[1]));
	}
		else
		printf("usage ./Philo [philos_number] [time_to_die] [time_\
to_eat] [time_to_sleep] [meal_needed]\n");
	return(0);
}