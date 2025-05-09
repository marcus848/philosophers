/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:02:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:48 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (ac < 5 || ac > 6)
		return (printf("ERROR: Wrong number of arguments\n"), 1);
	if (!check_inputs(ac, av))
		return (printf("ERROR: Wrong parameters\n"), 1);
	table = start_table(ac, av);
	if (!table)
		return(printf("ERROR: Malloc table"), 1);


	

}

