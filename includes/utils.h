/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bat <bat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:16:00 by bat               #+#    #+#             */
/*   Updated: 2023/07/18 11:43:59 by bat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "philosophers.h"
# include <sys/time.h>
# include <stdlib.h>

// utils.c
void	set_state(t_philo *philos, int n, t_state state);
t_state	get_state(t_philo *philos, int n);
void	ft_wait_ms(int n);
long long	get_time_ms(void);
void	ft_putendl_fd(char *s, int fd);
int ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
