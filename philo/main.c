/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:02:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/24 15:03:44 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void	*routine(void *arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;
	long			now;
	int	i = 0;

	while (++i <= 3)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->meal_lock);
		philo->last_meal_time = get_current_time_ms();
		pthread_mutex_unlock(&philo->meal_lock);
		now = get_current_time_ms() - philo->start_time;
		printf("%ld Philosopher %d is eating\n", now, philo->id);
		usleep(200000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		now = get_current_time_ms() - philo->start_time;
		printf("%ld Philosopher %d is sleeping\n", now, philo->id);
		usleep(100000);
		now = get_current_time_ms() - philo->start_time;
		printf("%ld Philosopher %d is thinking\n", now, philo->id);
	}
	return (NULL);
}

void	*routine_monitor(void *arg)
{
	t_philosopher	*philos = (t_philosopher *) arg;
	int	i;
	long	now;
	long	time_since_last_meal;

	while(1)
	{
		i = 0;
		while (i < 2)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			now = get_current_time_ms();
			time_since_last_meal = now - philos[i].last_meal_time;
			pthread_mutex_unlock(&philos[i].meal_lock);
			if (time_since_last_meal >= 400 + 1)
			{
				printf("%ld Philosophers %d died\n", now - philos[i].start_time, philos[i].id);
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t		threads[2];
	pthread_t		monitor_thread;
	t_philosopher	philosophers[2];
	pthread_mutex_t	forks[2];
	long			start;
	int				i;

	i = 0;
	while (i < 2)
		pthread_mutex_init(&forks[i++], NULL);
	start = get_current_time_ms();
	i = 0;
	while (i < 2)
	{
		philosophers[i].id = i + 1;
		philosophers[i].start_time = start;
		philosophers[i].last_meal_time = start;
		pthread_mutex_init(&philosophers[i].meal_lock, NULL);
		philosophers[i].left_fork = &forks[i];
		philosophers[i].right_fork = &forks[(i + 1) % 2];
		pthread_create(&threads[i], NULL, routine, &philosophers[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, routine_monitor, philosophers);
	i = 0;
	while (i < 2)
		pthread_join(threads[i++], NULL);
	pthread_detach(monitor_thread);
	i = 0;
	while (i < 2)
	{
		pthread_mutex_destroy(&forks[i++]);
		pthread_mutex_destroy(&philosophers[i].meal_lock);
		i++;
	}
	return (0);
}

