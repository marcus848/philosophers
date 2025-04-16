/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:07:00 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/31 16:44:34 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_table	*start_table(int ac, char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->is_ended = 0;
	table->start_time = get_time();
	table->n_philos = ft_atol(av[1]);	
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->times_must_eat = ft_atol(av[5]);
	else
		table->times_must_eat = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philos);	
	table->philos = malloc(sizeof(t_philo) * table->n_philos);
	init_forks(table);
	init_philos(table);
	safe_mutex(table, &table->table_lock, INIT);
	return (table);
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
		pthread_mutex_init(&table->forks[i++], NULL);
	i = 0;
	while (i < table->n_philos)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->n_philos];
		i++;
	}
}

void	init_philos(t_table *table)
{
	int	i;
	long	current_time;

	i = 0;
	current_time = get_time();
	while (i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].table = table;
		table->philos[i].meals_eaten = 0;
		table->philos[i].last_meal_time = current_time;
		safe_mutex(table, &table->philos[i].meal_lock, INIT);
		i++;
	}
}
