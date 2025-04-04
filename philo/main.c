/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:02:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/31 16:42:12 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (1);
	if (!check_inputs(ac, av))
		terminate_error("Invalid parameters", 1);
	table = start_table(ac, av);
	if (!table)
		terminate_error("Malloc table", 1);
	

}

// void	start_philo(t_table *table)
// {
// 	pthread_t	monitor;
// 	int		i;
// 	
// }

