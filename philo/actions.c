/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:43:57 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/31 15:18:59 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_philo *philo, t_table *table)
{
	uint64_t	now;

	now = get_time() - philo->start_time;
	if (!someone_died(table) && !someone_satisfied(table))
	{
		printf("%ld Philosopher %d is sleeping\n", now, philo->id);
		ft_usleep(200);
	}
}

void	think(t_philo *philo, t_table *table)
{
	uint64_t	now;

	now = get_time() - philo->start_time;
	if (!someone_died(table) && !someone_satisfied(table))
		printf("%ld Philosopher %d is thinking\n", now, philo->id);
}

void	eat(t_philo *philo, t_table *table)
{
	uint64_t	now;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	
	if (philo->left_fork < philo->right_fork)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	now = get_time() - philo->start_time;
	if (!someone_died(table) && !someone_satisfied(table))
		printf("%ld Philosopher %d has taken a fork\n", now, philo->id);
	pthread_mutex_lock(second_fork);
	now = get_time() - philo->start_time;
	if (!someone_died(table) && !someone_satisfied(table))
		printf("%ld Philosopher %d has taken a fork\n", now, philo->id);
	now = get_time() - philo->start_time;
	if (!someone_died(table) && !someone_satisfied(table))
	{
		printf("%ld Philosopher %d is eating\n", now, philo->id);
		ft_usleep(200);
	}
	philo->meals_eaten++;
	if (philo->meals_eaten == table->times_must_eat)
		table->count_satisfied++;
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
