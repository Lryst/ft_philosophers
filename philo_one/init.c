/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/14 14:14:11 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex_tab(t_info *info)
{
	int i;

	i = 0;
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

void	init_fork(t_info *info, t_philo *philo)
{
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
	init_fork(info, philo);
}

int		init_thread_tab(t_info *info)
{
	long	chrono;

	chrono = get_time();
	info->i = 0;
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	while (info->i < info->arg1)
	{
		info->philo[info->i].r_turn = 0;
		info->i++;
	}
	info->i = 0;
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
	usleep(2);
	info->i = 1;
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
	monitor(info);
	return (1);
}
