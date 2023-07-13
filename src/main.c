/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:28:20 by bat               #+#    #+#             */
/*   Updated: 2023/07/12 11:19:38 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "utils.h"

int	main(int ac, char **av)
{
	t_arg	arg;
	t_philo	*philos;

	arg = parse_args(ac, av);
	if (arg.error)
		return (1);
	philos = init_philos_list(arg);
	if (!philos)
		return (1);
	launch_philos(philos, arg);
	verify_meals(philos, arg);
	destroy_philos_list(philos, arg);
	ft_wait_ms(1);
}
