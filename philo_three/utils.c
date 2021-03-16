/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:59 by lryst             #+#    #+#             */
/*   Updated: 2021/03/16 13:05:50 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long	get_time(void)
{
	struct timeval	tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}

int		ft_atoi_lite(char *str)
{
	int i;
	int nbr;

	i = -1;
	nbr = 0;
	if (str[i] == '-')
		return (-1);
	while (str[++i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		nbr = (nbr * 10) + (int)(str[i] - '0');
	}
	if (nbr == 0)
		return (-1);
	return (nbr);
}

/* int		monitor_check_count_meal(t_info *info)
{
	int i;

	i = 0;
	while (i < info->arg1 && info->philo[i].nbr_turn == 1)
		i++;
	if (i == info->arg1)
		return (1);
	return (0);
} */

/* int		philo_die(t_info *info, int i)
{
	sem_close(info->totem);
	sem_unlink("/totem");
	if ((info->totem = sem_open("/totem", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (0);
	sem_wait(info->totem);
	printf("%ldms %d die\n", (get_time() - info->philo[i].top), i);
	i = 0;
	while (i < info->arg1)
	{
		sem_post(info->sem);
		info->philo[i++].start = 0;
	}
	sem_post(info->totem);
	return (1);
} */

void		monitor(void *tmp)
{
	t_philo *philo;

	philo = (t_philo*)tmp;
	while (1)
	{
		usleep(7);
		if (philo->nbr_turn == 1)
			break ;
		if ((get_time() - (philo->l_chrono)) > philo->life)
		{
			philo->start = 1;
			sem_wait(philo->totem);
			printf("%ldms %d die\n", (get_time() - philo->top), i);
			break ;
		}
	}
	return (NULL);
}
