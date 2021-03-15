/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/15 14:54:58 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	info->i = i;
	while (info->i < info->arg1)
	{
		init_philo_param(info, &info->philo[info->i]);
		if (pthread_create(&info->philo[info->i].thread, NULL,
			(void*)test, &info->philo[info->i]) != 0)
		{
			write(1, "pair GameOver\n", 14);
			return (0);
		}
		info->i += 2;
	}
	return (1);
}

int		init_thread_tab(t_info *info)
{
	sem_close(info->totem);
	sem_unlink("/totem");
	info->i = 0;
	sem_close(info->sem);
	sem_unlink("/eat");
	if ((info->totem = sem_open("/totem", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (0);
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	if ((info->sem = sem_open("/eat", O_CREAT, S_IRWXU, info->arg1 / 2))
		== SEM_FAILED)
		return (0);
	if (lauch_philo(info, 0) == 0)
		return (0);
	usleep(2);
	if (lauch_philo(info, 1) == 0)
		return (0);
	monitor(info);
	/* sem_close(info->sem);
	sem_unlink("/eat"); */
	/* sem_close(info->totem);
	sem_unlink("/totem"); */
	return (1);
}
