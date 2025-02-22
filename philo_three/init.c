/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/19 14:04:37 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		init_philo_param(t_info *info, t_philo *philo)
{
	philo->nbr = info->arg1;
	philo->life = info->arg2;
	philo->eat = info->arg3;
	philo->sleep = info->arg4;
	if (info->arg5 != -1)
		philo->turn = info->arg5;
	philo->i = info->i;
	philo->start = 0;
	philo->status = 1;
	philo->r_turn = 0;
	philo->sem = &info->sem;
	philo->totem = &info->totem;
	philo->l_chrono = get_time();
	philo->top = info->top_chrono;
}

void		lauch_philo(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, (void*)monitor, philo) != 0)
	{
		write(1, "GameOver\n", 9);
		return ;
	}
	while (philo->start != 1 && philo->nbr_turn != 1)
	{
		if (philo->start == 1 || philo->nbr_turn == 1 ||
			philo_eat(philo) == 1)
			break ;
		if (philo->start == 1 || philo->nbr_turn == 1 ||
			philo_sleep(philo) == 1)
			break ;
		if (philo->start == 1 || philo->nbr_turn == 1 ||
			philo_think(philo) == 1)
			break ;
	}
	pthread_join(thread, NULL);
	sem_close(*philo->totem);
	sem_close(*philo->sem);
}

static void	proc_philo(t_info *info, int u, int status)
{
	int i;

	i = 0;
	while (info->philo[u].start != 1 && ++u < info->arg1)
	{
		if (waitpid(-1, &status, 0) < 0)
			write(1, "Waitpid failed\n", 15);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
				if (++i == info->arg1)
					printf("All the philosophers ate %d times\n", info->arg5);
			if (WEXITSTATUS(status) == 0)
			{
				u = -1;
				while (++u < info->arg1)
					kill(info->philo[u].id, SIGINT);
				free(info->philo);
				sem_unlink("/fork");
				sem_unlink("/totem");
				exit(0);
			}
		}
	}
}

static int	init_semaphore(t_info *info)
{
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	sem_unlink("/fork");
	sem_unlink("/totem");
	memset(&info->sem, 0, sizeof(info->sem));
	if (SEM_FAILED == (info->sem = sem_open("/fork", O_CREAT, S_IRWXU,
		info->arg1 / 2)))
		return (0);
	memset(&info->totem, 0, sizeof(info->totem));
	if (SEM_FAILED == (info->totem = sem_open("/totem", O_CREAT, S_IRWXU, 1)))
		return (0);
	return (1);
}

int			init_thread_tab(t_info *info)
{
	info->i = 0;
	info->top_chrono = get_time();
	if (init_semaphore(info) == 0)
		return (0);
	while (info->i < info->arg1)
	{
		init_philo_param(info, &info->philo[info->i]);
		info->philo[info->i].id = fork();
		if (info->philo[info->i].id == 0)
		{
			lauch_philo(&info->philo[info->i]);
			if (info->philo[info->i].start)
				exit(0);
			exit(1);
		}
		info->i++;
	}
	proc_philo(info, -1, 0);
	free(info->philo);
	sem_unlink("/fork");
	sem_unlink("/totem");
	return (1);
}
