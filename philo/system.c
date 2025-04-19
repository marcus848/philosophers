/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:58:43 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:48 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
	t_table	*table = (t_table *)(philo - (philo->id - 1));

	return (NULL);
}

void	*monitor(void *arg)
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
			pthread_mutex_lock(&table->philos[i].lock);
			now = get_time();
			time_since_last_meal = now - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->philos[i].lock);
			if (time_since_last_meal > 401)
			{
				pthread_mutex_lock(&table->table_lock);
				if (!table->is_dead)
				{
					printf("%ld Philosophers %d died\n", now - table->philos[i].start_time, table->philos[i].id);
					table->is_dead = 1;
				}
				pthread_mutex_unlock(&table->table_lock);
				return (NULL);
			}
			if (2 <= table->count_satisfied)
				table->is_satisfied = 1;
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}

int	someone_died(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->table_lock);
	dead = table->is_dead;
	pthread_mutex_unlock(&table->table_lock);
	return (dead);
}

int	someone_satisfied(t_table *table)
{
	int	satisfied;

	pthread_mutex_lock(&table->table_lock);
	satisfied = table->is_satisfied;
	pthread_mutex_unlock(&table->table_lock);
	return (satisfied);
}
