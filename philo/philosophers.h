/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:03:46 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/25 16:23:45 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>

# define TIME_TO_DIE 600

typedef struct s_philosopher
{
	int	id;
	long	start_time;
	long	last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	int		meals_eaten;
}	t_philo;

typedef struct	s_table
{
	t_philo	philos[2];
	pthread_mutex_t	forks[2];
	pthread_mutex_t	death_lock;
	int		is_dead;
}	t_table;

int	someone_died(t_table *table);

// utils
uint64_t	get_time(void);
int	ft_usleep(uint64_t time);

// actions
void	eat(t_philo *philo, t_table *table);
void	sleeping(t_philo *philo, t_table *table);
void	think(t_philo *philo, t_table *table);

#endif // !PHILOSOPHERS_H
