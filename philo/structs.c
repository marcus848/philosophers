/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:07:00 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/31 15:15:14 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

t_table	start_table(int ac, char **av)
{
	t_table	table;

	table.is_dead = 0;
	table.count_satisfied = 0;
	table.is_satisfied = 0;
	table.death_time = ft_atoi(av[2]);
	table.eat_time = ft_atoi(av[3]);
	table.sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		table.times_must_eat = ft_atoi(av[5]);
	else
		table.times_must_eat = -1;
	table.n_philos = ft_atoi(av[1]);	
	table.forks = malloc(sizeof(pthread_mutex_t) * table.n_philos);	
	table.philos = malloc(sizeof(t_philo) * table.n_philos);
	init_forks(&table);
	init_philos(&table);
	return (table);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
		pthread_mutex_init(&table->forks[i++], NULL);
	table->philos[0].left_fork = &table->forks[0];
	table->philos[0].right_fork = &table->forks[table->n_philos - 1];
	i = 1;
	while (i < table->n_philos)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[i - 1];
		i++;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		i++;
	}
}
