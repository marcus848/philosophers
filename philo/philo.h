/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:03:46 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 20:28:19 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>
# include <sys/time.h>

# define TIME_TO_DIE 600

typedef enum	e_mode
{
	INIT,
	LOCK,
	UNLOCK,
	DESTROY
}	t_mode;

typedef struct s_table t_table;

typedef struct s_philosopher
{
	int	id;
	int		meals_eaten;
	pthread_t	thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_lock;
	unsigned long	last_meal_time;
	t_table	*table;
}	t_philo;

typedef struct	s_table
{
	int		n_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int		times_must_eat;
	int		is_ended;
	pthread_t	monitor;
	unsigned long	start_time;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	table_lock;
	pthread_mutex_t	*forks;
	t_philo		*philos;
}	t_table;

int	someone_died(t_table *table);
int	someone_satisfied(t_table *table);

// utils
unsigned long	get_time(void);
int	ft_usleep(uint64_t time);
long     ft_atol(const char *nptr);
int	ft_isnbr(const char *str);
int	ft_strcmp(const char *s1, const char *s2);
void	print_message(t_philo *philo, char *msg);

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
void	error_exit(t_table *table, char *error);

// mutex
void	handle_mutex_errors(int status, t_mode mode);
void	safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode);

#endif // !PHILOSOPHERS_H
