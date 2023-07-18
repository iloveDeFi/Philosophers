/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:23:23 by bat               #+#    #+#             */
/*   Updated: 2023/07/18 11:35:27 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
#include "../includes/utils.h"

void	verify_meals(t_philo *philos, t_arg arg)
{
	int	n_freed;
	int	i;
	int	is_done;

	n_freed = 0;
	is_done = 0;
	while (n_freed < arg.number_of_philosophers && !is_done)
	{
		i = -1;
		n_freed = 0;
		while (++i < arg.number_of_philosophers && !is_done)
			is_done = philos_kill(philos, arg.time_to_die, i, &n_freed);
	}
	philos_kill_all(philos, arg.number_of_philosophers);
}

static int	philos_kill(t_philo *philos, int time_to_die, int i, int *n_freed)
{
	int			killed;

	killed = 0;
	if (get_state(philos, i) == freed)
		(*n_freed)++;
	else
	{
		if (get_time_ms() - philos[i].last_meal > time_to_die)
		{
			printf("%lld %d died\n", get_time_ms(), i + 1);
			killed = 1;
			pthread_mutex_lock(&philos[i].update);
			philos[i].state = dead;
			pthread_mutex_unlock(&philos[i].update);
		}
	}
	return (killed);
}

static void	philos_kill_all(t_philo *philos, int number_of_philosophers)
{
	int	i;

	i = -1;
	while (++i < number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].update);
		if (philos[i].state != freed)
			philos[i].state = dead;
		pthread_mutex_unlock(&philos[i].update);
	}
}
