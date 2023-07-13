/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:25:14 by bat               #+#    #+#             */
/*   Updated: 2023/07/12 11:19:42 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_state(t_philo *philos, int n, t_state state)
{
	pthread_mutex_lock(&philos[n].update);
	philos[n].state = state;
	pthread_mutex_unlock(&philos[n].update);
}

t_state	get_state(t_philo *philos, int n)
{
	t_state	state;

	state = philos[n].state;
	return (state);
}

void	ft_wait_ms(int n)
{
	long long	start;

	if (n <= 0)
		return ;
	start = get_time_ms();
	while (get_time_ms() - start < n)
		usleep(1000);
}

long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
