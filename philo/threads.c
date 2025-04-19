/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:24:11 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:48 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->times_must_eat == 0)
		return ;
	else
	{
		while (i < table->n_philos)
		{
			pthread_create(&table->philos[i].thread_id, NULL,
		  		routine, &table->philos[i]);
			i++;
		}
	}
}
