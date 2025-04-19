/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 10:58:43 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 21:33:48 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		safe_mutex(philo->table, &philo->table->table_lock, LOCK);
		if (philo->table->is_ended)
		{
			safe_mutex(philo->table, &philo->table->table_lock, UNLOCK);
			break ;
		}
		safe_mutex(philo->table, &philo->table->table_lock, UNLOCK);
	}
	return (NULL);
}

void	take_forks(t_philo *philo)
{
	char	*msg;

	msg = "has taken a fork";
	if (philo->id % 2 == 0)
	{
		safe_mutex(philo->table, philo->left_fork, LOCK);
		print_message(philo, msg);
		safe_mutex(philo->table, philo->right_fork, LOCK);
		print_message(philo, msg);
	}
	else
	{
		safe_mutex(philo->table, philo->right_fork, LOCK);
		print_message(philo, msg);
		safe_mutex(philo->table, philo->left_fork, LOCK);
		print_message(philo, msg);
	}
}

void	eat_sleep_think(t_philo *philo)
{
	safe_mutex(philo->table, &philo->meal_lock, LOCK);
	philo->last_meal_time = get_time();
	safe_mutex(philo->table, &philo->meal_lock, UNLOCK);
	print_message(philo, "is eating");
	usleep(philo->table->time_to_eat * 1000);
	safe_mutex(philo->table, &philo->meal_lock, LOCK);
	philo->meals_eaten++;
	safe_mutex(philo->table, &philo->meal_lock, UNLOCK);
	safe_mutex(philo->table, philo->left_fork, UNLOCK);
	safe_mutex(philo->table, philo->right_fork, UNLOCK);
	print_message(philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
	print_message(philo, "is thinking");
}
