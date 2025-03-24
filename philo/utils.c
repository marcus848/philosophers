/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:42:15 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/24 15:05:26 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
//
// int	ft_usleep(uint64_t time, t_philo *philo)
// {
// 	uint64_t	start;
//
// 	start = get_time(philo->data);
// 	while ((get_time(philo->data) - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }
