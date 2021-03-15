/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/15 14:32:58 by lryst            ###   ########.fr       */
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
	//exit (1);
}

void	lauch_philo(t_info *info, int i)
{
	pthread_t	thread;
	
	info->i = i;
	//init_philo_param(info, &info->philo[info->i]);
	if (pthread_create(&thread, NULL,
		(void*)monitor, &info->philo[info->i]) != 0)
	{
		write(1, "GameOver\n", 9);
		return ;
	}
}

int		init_thread_tab(t_info *info)
{
	info->i = 0;
	//exit (1);
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	while (info->i < info->arg1)
	{
		init_philo_param(info, &info->philo[info->i]);
		info->philo[info->i].id = fork();
		if (info->philo[info->i].id == 0)
		{
			lauch_philo(info, info->i);
			if (test(&info->philo[info->i]) == 0)
				exit (2);
		}
		info->i++;
	}
	info->i = 0;
	while (info->i < info->arg1)
	{
		waitpid(info->philo[info->i].id, NULL, WNOHANG);
	}
	return (1);
}
