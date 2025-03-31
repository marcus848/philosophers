/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:03:46 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/31 16:40:33 by marcudos         ###   ########.fr       */
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

typedef struct s_table t_table;

typedef struct s_philosopher
{
	t_table	*table;
	int	id;
	long	start_time;
	long	last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
	int		meals_eaten;
}	t_philo;

typedef struct	s_table
{
	int		n_philos;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	table_lock;
	int		is_dead;
	int		times_must_eat;
	int		count_satisfied;
	int		is_satisfied;
	int		death_time;
	int		eat_time;
	int		sleep_time;
}	t_table;

int	someone_died(t_table *table);
int	someone_satisfied(t_table *table);

// utils
uint64_t	get_time(void);
int	ft_usleep(uint64_t time);
int     ft_atoi(const char *nptr);

// actions
void	eat(t_philo *philo, t_table *table);
void	sleeping(t_philo *philo, t_table *table);
void	think(t_philo *philo, t_table *table);

// system
void	*routine(void *arg);
void	*monitor(void *arg);

// structs
t_table	*start_table(int ac, char **av);
void	init_forks(t_table *table);
void	init_philos(t_table *table);

// error
int	check_inputs(int ac, char **av);
void	terminate_error(char *msg, int code);

#endif // !PHILOSOPHERS_H
