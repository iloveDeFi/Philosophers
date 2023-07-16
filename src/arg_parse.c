/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:21:43 by bat               #+#    #+#             */
/*   Updated: 2023/07/16 12:06:51 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_arg	parse_args(int ac, char **av)
{
	t_arg	arg;

	arg.error = 0;
	if (!(5 <= ac && ac <= 6))
		return (parse_error(&arg));
	arg.number_of_philosophers = ft_atoi(av[1]);
	arg.time_to_die = ft_atoi(av[2]);
	arg.time_to_eat = ft_atoi(av[3]);
	arg.time_to_sleep = ft_atoi(av[4]);
	arg.number_of_times_each_philosopher_must_eat = -1;
	if (ac == 6)
	{
		arg.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
		if (arg.number_of_times_each_philosopher_must_eat < 0)
			return (parse_error(&arg));
	}
	return (arg);
}

t_arg	parse_error(t_arg *arg)
{
	ft_putendl_fd("Error: argument", 1);
	arg->error = 1;
	return (*arg);
}

void	print_args(t_arg arg)
{
	if (arg.error)
	{
		printf("Error has been found\n");
		return ;
	}
	printf("%d ", arg.number_of_philosophers);
	printf("%d ", arg.time_to_die);
	printf("%d ", arg.time_to_eat);
	printf("%d ", arg.time_to_sleep);
	printf("%d\n", arg.number_of_times_each_philosopher_must_eat);
}
