/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:24:48 by bat               #+#    #+#             */
/*   Updated: 2023/07/12 11:19:36 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

t_philo	*init_philos_list(t_arg arg)
{
	t_philo	*philos;
	int		i;

	philos = ft_calloc(arg.number_of_philosophers, sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < arg.number_of_philosophers)
	{
		pthread_mutex_init(&(philos[i].fork), NULL);
		pthread_mutex_init(&(philos[i].update), NULL);
		philos[i].state = sleeping;
	}
	return (philos);
}

void	destroy_philos_list(t_philo *philos, t_arg arg)
{
	int	i;

	i = -1;
	while (++i < arg.number_of_philosophers)
	{
		while (get_state(philos, i) != freed)
			usleep(1000);
		pthread_mutex_destroy(&(philos[i].fork));
		pthread_mutex_destroy(&(philos[i].update));
	}
	free(philos);
}
