/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:49:20 by lryst             #+#    #+#             */
/*   Updated: 2021/03/16 13:11:33 by lryst            ###   ########.fr       */
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
	philo->r_turn = 0;
	philo->sem = info->sem;
	philo->totem = info->totem;
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
		if (philo->start == 1 || philo->nbr_turn == 1 || philo_eat(philo) == 1)
			break ;
		if (philo->start == 1 || philo->nbr_turn == 1 || philo_sleep(philo) == 1)
			break ;
		if (philo->start == 1 || philo->nbr_turn == 1 || philo_think(philo) == 1)
			break ;
	}
	pthread_join(thread, NULL);
	sem_close(philo->sem);
}

static void	proc_philo(t_info *info, int k, int status)
{
	int i;

	i = 0;
	while (info->philo[k].start != 1 && ++k < info->arg1)
	{
		if (waitpid(-1, &status, 0) == -1)
			write(1, "Waitpid failed\n", 15);
		if (WEXITSTATUS)
		{
			if (WEXITSTATUS == 1)
				if (++i == info->arg1)
					printf("All the philosophers ate %d times\n", info->arg5);
			if (WEXITSTATUS == 0)
			{
				k = -1;
				while (++k < info->arg1)
					kill (info->philo[k].id, SIGKILL);
				free(info->philo);
				sem_unlink("/fork");
				sem_unlink("/totem");
			}
		}
	}
}

int			init_thread_tab(t_info *info)
{
	int i;
	
	info->i = 0;
	info->top_chrono = get_time();
	sem_unlink("/fork");
	if (!(info->philo = (t_philo*)malloc(sizeof(t_philo) * info->arg1)))
		return (0);
	if ((info->sem = sem_open("/fork", O_CREAT, S_IRWXU, info->arg1 / 2))
		== SEM_FAILED)
		return (0);
	if ((info->sem = sem_open("/totem", O_CREAT, S_IRWXU, 1))
		== SEM_FAILED)
		return (0);
	sem_post(info->totem);
	while (info->i < info->arg1)
	{
		init_philo_param(info, &info->philo[info->i]);
		info->philo[info->i].id = fork();
		if (info->philo[info->i].id == 0)
		{
			lauch_philo(&info->philo[i]);
			info->start = info->philo[i].start;
			if (info->philo[i].start)
				exit (0);
			exit (1);
		}
		info->i++;
	}
	proc_philo(info, -1, 0);
	free(info->philo);
	sem_unlink("/fork");
	sem_unlink("/totem");
	return (1);
}


/* fork
create thread ->
*/

