/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:28:18 by bat               #+#    #+#             */
/*   Updated: 2023/07/18 10:26:30 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum e_state
{
	eating,
	sleeping,
	thinking,
	stopping,
	dead,
	freed
}	t_state;

typedef struct s_args
{
    int time_to_eat;
    int time_to_die;
    int time_to_sleep;
    int number_of_philosophers;
    int number_of_times_each_philosopher_must_eat;
    int error;
}   t_arg;

typedef struct s_philo
{
    t_state         state;
    pthread_mutex_t	update;
	pthread_mutex_t	fork;
    long long       last_meal;
}   t_philo;

typedef struct s_launch
{
    int         n;
    t_arg       arg;
    t_philo     *philos;
}   t_launch;

// arg_parse.c
t_arg   parse_args(int ac, char **av);
t_arg	parse_error(t_arg *arg);
void	print_args(t_arg arg);

// kill.c
void	verify_meals(t_philo *philos, t_arg arg);
static int  philos_kill(t_philo *philos, int time_to_die, int i, int *n_freed);
static void philos_kill_all(t_philo *philos, int number_of_philosophers);

// launch.c
int		launch_philos(t_philo *philos, t_arg arg);
static int	launch_philo(t_philo *philos, t_arg arg, int n);

// list.c
t_philo	*init_philos_list(t_arg arg);
void	destroy_philos_list(t_philo *philos, t_arg arg);

// main.c
int	main(int ac, char **av);

// threads.c
void	*philo_start(void *launch);
static t_state	philo_action(t_launch *l, int *n_eaten);
static int	get_left_fork_n(int n, int number_of_philosophers);
static void		philo_exec_action(t_launch *l, t_state state, int n_eaten);
static void		eat(t_launch *l);

#endif