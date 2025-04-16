/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:29:08 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/16 16:51:22 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_mutex(t_table *table, pthread_mutex_t *mutex, t_mode mode)
{
	if (mode == INIT)
		handle_mutex_errors(pthread_mutex_init(mutex, NULL), mode);
	else if (mode == LOCK)
		handle_mutex_errors(pthread_mutex_lock(mutex), mode);
	else if (mode == UNLOCK)
		handle_mutex_errors(pthread_mutex_unlock(mutex), mode);
	else if (mode == DESTROY)
		handle_mutex_errors(pthread_mutex_destroy(mutex), mode);
	else
		error_exit(table, "Mutex code error\n");
}

void	handle_mutex_errors(int status, t_mode mode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (mode == LOCK || mode == UNLOCK
			|| mode == DESTROY))
		printf("Invalid mutex operation\n");
	else if (status == EINVAL && mode == INIT)
		printf("Invalid attr for mutex init\n");
	else if (status == EDEADLK)
		printf("Deadlock detected\n");
	else if (status == EPERM)
		printf("Permission denied\n");
	else if (status == ENOMEM)
		printf("Out of memory\n");
	else if (status == EBUSY)
		printf("Mutex is locked\n");
	else
		printf("Unknown mutex error\n");

}
