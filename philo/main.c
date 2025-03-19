/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:02:31 by marcudos          #+#    #+#             */
/*   Updated: 2025/03/19 13:56:32 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void*	routine(void* arg)
{
	t_philosopher	*philo = (t_philosopher *)arg;

	printf("philosophers %d is eating\n", philo->id);
	printf("philosophers %d is thinking\n", philo->id);
	printf("philosophers %d is sleeping\n", philo->id);
	return NULL;
}

int	main(void)
{
	pthread_t	threads[2];
	t_philosopher	philosophers[2];
	int	i;

	i = 0;
	while (i < 2)
	{
		philosophers[i].id = i + 1;
		pthread_create(&threads[i], NULL, routine, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < 2)
		pthread_join(threads[i++], NULL);
	return (0);
}
