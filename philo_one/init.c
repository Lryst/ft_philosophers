/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/10 07:28:25 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex_tab(t_info *info)
{
	int i;

	i = 0;
	//printf("%d\n", info->arg1);
	if (!(info->mutex_tab = (t_mutex*)malloc(sizeof(t_mutex) * info->arg1)))
		return (0);
	while (i < info->arg1)
	{
		pthread_mutex_init(&info->mutex_tab[i].mutex, NULL);
		info->mutex_tab[i].latest = -1;
		i++;
	}
	return (1);
}

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
	if (philo->i == 0)
	{
		philo->mutex_r = &info->mutex_tab[philo->i + 1];
		philo->mutex_l = &info->mutex_tab[0];
	}
	if (philo->i == philo->nbr - 1)
	{
		philo->mutex_r = &info->mutex_tab[0];
		philo->mutex_l = &info->mutex_tab[philo->nbr - 1];
	}
	else
	{
		philo->mutex_r = &info->mutex_tab[philo->i + 1];
		philo->mutex_l = &info->mutex_tab[philo->i];
	}
}

int     init_thread_tab(t_info *info)
{
	//exit (1);
	info->i = 0;
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	while (info->i < info->arg1)
	{
		info->philo[info->i].r_turn = 0;
		info->i++;
	}
	//exit (1);
	info->i = 0;
	//printf("\nS 1 TRUCT\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->arg1, info->arg2, info->arg3, info->arg4);
	while (info->i < info->arg1)
	{
		//info->philo[info->i].start = 0;
		init_philo_param(info, &info->philo[info->i]);
		//printf("%d - philo->i = %d\n", info->i, info->philo[info->i].i);
		//info->philo[info->i].i = info->i;
		//exit (1);
		if (pthread_create(&info->philo[info->i].thread, NULL, (void*)test, &info->philo[info->i]) != 0)
		{
			write(1, "pair GameOver\n", 14);
			return (0);
		}
		//usleep(10);
		info->i++;
	}
	monitor(info);
	//printf("\n 2 STRUCT\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->arg1, info->arg2, info->arg3, info->arg4);
	return (1);
}