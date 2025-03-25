/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:02:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/25 16:23:57 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	someone_died(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->death_lock);
	dead = table->is_dead;
	pthread_mutex_unlock(&table->death_lock);
	return (dead);
}

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_table	*table = (t_table *)(philo - (philo->id - 1));
	int	i = 0;

	while (++i <= 3 && !someone_died(table))
	{
		eat(philo, table);
		sleeping(philo, table);
		think(philo, table);

	}
	return (NULL);
}

void	*routine_monitor(void *arg)
{
	t_table	*table = (t_table *) arg;
	int	i;
	uint64_t	now;
	long	time_since_last_meal;

	while(1)
	{
		i = 0;
		while (i < 2)
		{
			pthread_mutex_lock(&table->philos[i].meal_lock);
			now = get_time();
			time_since_last_meal = now - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->philos[i].meal_lock);
			if (time_since_last_meal >= TIME_TO_DIE)
			{
				pthread_mutex_lock(&table->death_lock);
				if (!table->is_dead)
				{
					printf("%ld Philosophers %d died\n", now - table->philos[i].start_time, table->philos[i].id);
					table->is_dead = 1;
				}
				pthread_mutex_unlock(&table->death_lock);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	main(void)
{
	t_table	table;
	pthread_t	threads[2];
	pthread_t	monitor_thread;
	long	start;
	int				i;

	i = 0;
	while (i < 2)
		pthread_mutex_init(&table.forks[i++], NULL);
	pthread_mutex_init(&table.death_lock, NULL);	
	table.is_dead = 0;
	start = get_time();
	i = 0;
	while (i < 2)
	{
		table.philos[i].id = i + 1;
		table.philos[i].start_time = start;
		table.philos[i].last_meal_time = start;
		pthread_mutex_init(&table.philos[i].meal_lock, NULL);
		table.philos[i].left_fork = &table.forks[i];
		table.philos[i].right_fork = &table.forks[(i + 1) % 2];
		pthread_create(&threads[i], NULL, routine, &table.philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, routine_monitor, table.philos);
	i = 0;
	while (i < 2)
		pthread_join(threads[i++], NULL);
	pthread_detach(monitor_thread);
	i = 0;
	while (i < 2)
	{
		pthread_mutex_destroy(&table.forks[i++]);
		pthread_mutex_destroy(&table.philos[i].meal_lock);
		i++;
	}
	return (0);
}

