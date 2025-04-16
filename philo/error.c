/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:23:16 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/16 16:50:31 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_inputs(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!ft_isnbr(av[i]))
			return (0);
		i++;
	}
	return (1);
}

void	error_exit(t_table *table, char *error)
{
	safe_mutex(table, &table->write_lock, LOCK);
	printf("%s", error);
	safe_mutex(table, &table->write_lock, UNLOCK);
}
