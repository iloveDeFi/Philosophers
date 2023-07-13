/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:24:15 by bat               #+#    #+#             */
/*   Updated: 2023/07/11 17:24:28 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

int	launch_philos(t_philo *philos, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.number_of_philosophers)
	{
		if (launch_philo(philos, arg, i))
			return (1);
		i += 2;
		if (i % 2 == 0 && i >= arg.number_of_philosophers)
			i = 1;
	}
	return (0);
}

static int	launch_philo(t_philo *philos, t_arg arg, int n)
{
	t_launch	*launch;
	pthread_t	thread;

	launch = ft_calloc(1, sizeof(t_launch));
	if (!launch)
		return (1);
	launch->arg = arg;
	launch->philos = philos;
	launch->n = n;
	launch->philos[n].last_meal = get_time_ms();
	if (pthread_create(&thread, NULL, &philo_start, launch))
		return (1);
	pthread_detach(thread);
	return (0);
}
