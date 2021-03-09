/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 09:28:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex_tab(t_mutex **mutex_tab, int len)
{
	int	i;

	i = 0;
	if (!(mutex_tab = (t_mutex**)malloc(sizeof(t_mutex*) * len + 1)))
		return (0);
	while (i < len)
	{
		if (!(mutex_tab[i] = (t_mutex*)malloc(sizeof(t_mutex) * 1 + 1)))
			return (0);
		pthread_mutex_init(&mutex_tab[i]->mutex, NULL);
		//exit (1);
		mutex_tab[i]->latest = -1;
		//exit (1);
		i++;
	}
	mutex_tab[i] = NULL;
	return (1);
}

int	init_philo_param(t_info *info, t_philo *philo)
{
	philo->nbr = info->arg1;
	philo->life = info->arg2;
	philo->eat = info->arg3;
	philo->sleep = info->arg4;
	if (info->arg5 != -1)
		philo->turn = info->arg5;
	philo->i = info->i;
	/* if ((init_mutex_tab(philo->mutex_tab, philo->nbr)) == 0)
		return (free_mutex_tab(philo->mutex_tab)); */
	int	i;

	i = 0;
	if (!(philo->mutex_tab = (t_mutex**)malloc(sizeof(t_mutex*) * philo->nbr + 1)))
		return (0);
	while (i < philo->nbr)
	{
		if (!(philo->mutex_tab[i] = (t_mutex*)malloc(sizeof(t_mutex) * 1 + 1)))
			return (0);
		pthread_mutex_init(&philo->mutex_tab[i]->mutex, NULL);
		//exit (1);
		philo->mutex_tab[i]->latest = -1;
		//exit (1);
		i++;
	}
	philo->mutex_tab[i] = NULL;
	
	//exit (1);
	//printf("\nSTRUCT\ni = %d\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", philo->i, philo->nbr, philo->life, philo->eat, philo->sleep);
	//printf("latest = %d\n", philo->mutex_tab[philo->i]->latest);
	//exit (1);
	philo->mutex_tab = info->mutex_tab;
	philo->start = 2;
	philo->r_turn = 0;
	philo->start_chrono = get_time() - philo->start_chrono;
	return (1);
}

int     init_thread_tab(t_info *info)
{
	info->i = 0;
	//pthread_mutex_init(&info->totem, NULL);
	//pthread_mutex_unlock(&info->totem);
	if (!(info->philo = (t_philo**)malloc(sizeof(t_philo*) * info->arg1 + 1)))
		return (0);
	while (info->i < info->arg1)
	{
		//printf("i = %d\n", info->i);
		if (!(info->philo[info->i] = (t_philo*)malloc(sizeof(t_philo) * 1 + 1)))
			return (0);
		info->philo[info->i]->r_turn = 0;
		info->i++;
	}
	//exit(1);
	info->philo[info->i] = NULL;
	info->i = 0;
	//exit(1);
	printf("\nS 1 TRUCT\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->arg1, info->arg2, info->arg3, info->arg4);
	while (info->i < info->arg1)
	{
		if (init_philo_param(info, info->philo[info->i]) == 0)
			return (0);
		//exit(1);
		info->philo[info->i]->start = 0;
		printf("\ninfo->i = %d\n", info->i);
		if (pthread_create(&info->philo[info->i]->thread, NULL, (void*)test, info) != 0)
		{
			write(1, "pair GameOver\n", 14);
			return (0);
		}
		//info->philo[info->i]->start = 0;
		if (info->i + 1 < info->arg1)
			info->i++;
		else
			break;
	}
	//exit (1);
	info->i = 0;
	while (info->i < info->arg1)
	{
		info->philo[info->i]->start = 1;
		info->i++;
	}
	monitor(info);
/* 	info->i = 1;
	while (info->i < info->nbr)
	{
		if (pthread_create(&info->philo[info->i]->thread, NULL, (void *)test, info) != 0)
		{
			write(1, "pair GameOver\n", 14);
			return (0);
		}
		info->philo[info->i]->start = 1;
		if (info->philo[info->i + 2])
			info->i += 2;
		else
		{
			break ;
		}
	} */
	printf("\n 2 STRUCT\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->arg1, info->arg2, info->arg3, info->arg4);
	return (1);
}