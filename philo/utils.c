/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:42:15 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/18 19:42:52 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(uint64_t ms)
{
	uint64_t	end;

	end = get_time() + ms;
	while (get_time() < end)
		usleep(100);
	return (0);
}

long     ft_atol(const char *nptr)
{
	long     sinal;
	long     nbr;

	sinal = 1;
	nbr = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		nptr++;
		sinal *= -1;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + *nptr - '0';
		nptr++;
	}
	return (nbr * sinal);
}

int	ft_isnbr(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9')) 
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	return (0);
}

void	print_message(t_philo *philo, char *msg)
{
	unsigned long	time;

	if (ft_strcmp(msg, "died"))
	{
		safe_mutex(philo->table, &philo->table->table_lock, LOCK);
		if (philo->table->is_ended)
		{
			safe_mutex(philo->table, &philo->table->table_lock, UNLOCK);
			return ;
		}
		safe_mutex(philo->table, &philo->table->table_lock, UNLOCK);
	}
	safe_mutex(philo->table, &philo->table->write_lock, LOCK);
	time = get_time() - philo->table->start_time;
	printf("%lu %d %s\n",time, philo->id, msg);
	safe_mutex(philo->table, &philo->table->write_lock, UNLOCK);
}
