/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/14 17:06:22 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	init_philo_param(t_info *info, t_philo *philo)
{
	philo->nbr = info->arg1;
	philo->life = info->arg2;
	philo->eat = info->arg3;
	philo->sleep = info->arg4;
	if (info->arg5 != -1)
		philo->turn = info->arg5;
	philo->i = info->i;
	philo->start = 1;
	philo->r_turn = 0;
	philo->sem = info->sem;
	philo->totem = info->totem;
}

int		lauch_philo(t_info *info, int i)
{
	pthread_t	thread;
	info->i = i;
	init_philo_param(info, &info->philo[info->i]);
	if (pthread_create(&thread, NULL,
		(void*)test, &info->philo[info->i]) != 0)
	{
		write(1, "pair GameOver\n", 14);
		return (0);
	}
	info->i += 2;
}

int		init_thread_tab(t_info *info)
{
	info->i = 0;
	while (info->i < info->arg1)
	{
		info->philo[i].id = fork()
	}
	return (1);
}
