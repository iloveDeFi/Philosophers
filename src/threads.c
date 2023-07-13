/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:22:27 by bat               #+#    #+#             */
/*   Updated: 2023/07/12 11:19:40 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

void	*philo_start(void *launch)
{
	t_philo	*philos;
	int		n;
	int		n_eaten;
	t_state	state;

	philos = ((t_launch *)launch)->philos;
	n = ((t_launch *)launch)->n;
	n_eaten = 0;
	state = sleeping;
	if (n % 2 != 0)
		ft_wait_ms(3);
	while (state != dead && state != stopping)
	{
		if (((t_launch *)launch)->arg.number_of_philosophers == 1)
		{
			usleep(250);
			state = get_state(philos, n);
		}
		else
			state = philo_action((t_launch *)launch, &n_eaten);
	}
	free(launch);
	set_state(philos, n, freed);
	return (NULL);
}

static t_state	philo_action(t_launch *l, int *n_eaten)
{
	t_state	state;

	pthread_mutex_lock(&l->philos[l->n].update);
	if (l->philos[l->n].state == dead
		|| !l->arg.number_of_times_each_philosopher_must_eat)
		state = dead;
	else if (l->philos[l->n].state == eating)
	{
		l->philos[l->n].state = sleeping;
		state = sleeping;
	}
	else if (0 > l->arg.number_of_times_each_philosopher_must_eat
		|| (*n_eaten)++
		< l->arg.number_of_times_each_philosopher_must_eat - 1)
		state = eating;
	else
		state = stopping;
	pthread_mutex_unlock(&l->philos[l->n].update);
	philo_exec_action(l, state, *n_eaten);
	return (state);
}

static int	get_left_fork_n(int n, int number_of_philosophers)
{
	int	n_left;

	n_left = n - 1;
	if (n_left < 0)
		n_left = number_of_philosophers - 1;
	return (n_left);
}

static void	philo_exec_action(t_launch *l, t_state state, int n_eaten)
{
	if (state == eating || state == stopping)
	{
		if (n_eaten > 1)
			printf("%lld %d is thinking\n", get_time_ms(), l->n + 1);
		while (get_state(l->philos, get_left_fork_n(l->n,
					l->arg.number_of_philosophers)) == thinking)
			usleep(500);
		pthread_mutex_lock(&l->philos[l->n].update);
		if (l->philos[l->n].state == dead)
		{
			pthread_mutex_unlock(&l->philos[l->n].update);
			return ;
		}
		l->philos[l->n].state = thinking;
		pthread_mutex_unlock(&l->philos[l->n].update);
		pthread_mutex_lock(&l->philos[get_left_fork_n(l->n,
				l->arg.number_of_philosophers)].fork);
		eat(l);
	}
	else if (state == sleeping)
	{
		printf("%lld %d is sleeping\n", get_time_ms(), l->n + 1);
		ft_wait_ms(l->arg.time_to_sleep);
	}
}

static void	eat(t_launch *l)
{
	int	n_left;

	n_left = get_left_fork_n(l->n, l->arg.number_of_philosophers);
	if (get_state(l->philos, l->n) == dead)
	{
		pthread_mutex_unlock(&l->philos[n_left].fork);
		return ;
	}
	printf("%lld %d has taken a fork\n", get_time_ms(), l->n + 1);
	pthread_mutex_lock(&l->philos[l->n].fork);
	if (get_state(l->philos, l->n) != dead)
		printf("%lld %d has taken a fork\n", get_time_ms(), l->n + 1);
	pthread_mutex_lock(&l->philos[l->n].update);
	if (l->philos[l->n].state != dead)
	{
		l->philos[l->n].state = eating;
		l->philos[l->n].last_meal = get_time_ms();
		pthread_mutex_unlock(&l->philos[l->n].update);
		printf("%lld %d is eating\n", get_time_ms(), l->n + 1);
		ft_wait_ms(l->arg.time_to_eat);
	}
	else
		pthread_mutex_unlock(&l->philos[l->n].update);
	pthread_mutex_unlock(&l->philos[l->n].fork);
	pthread_mutex_unlock(&l->philos[n_left].fork);
}
