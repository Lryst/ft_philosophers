/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:59 by lryst             #+#    #+#             */
/*   Updated: 2021/03/20 20:56:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

int		monitor_check_count_meal(t_info *info)
{
	int i;

	i = 0;
	while (i < info->arg1 && info->philo[i].nbr_turn == 1)
		i++;
	if (i == info->arg1)
		return (1);
	return (0);
}

int		philo_die(t_info *info, int i)
{
	pthread_mutex_lock(&info->totem);
	printf("%ldms %d die\n", (get_time() - info->philo[i].top), i + 1);
	i = 0;
	while (i < info->arg1)
		info->philo[i++].start = 0;
	usleep(10);
	i = 0;
	while (i < info->arg1)
		pthread_mutex_destroy(&info->mutex_tab[i++].mutex);
	pthread_mutex_destroy(&info->totem);
	free(info->philo);
	free(info->mutex_tab);
	return (0);
}

int		monitor(t_info *info)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < info->arg1)
		{
			if (info->philo[i].nbr_turn == 1)
			{
				if (monitor_check_count_meal(info) == 1)
				{
					printf("All the philosophers ate %d times\n", info->arg5);
					return (1);
				}
			}
			usleep(7);
			if ((get_time() - (info->philo[i].l_chrono)) > info->philo[i].life)
				return (philo_die(info, i));
			i++;
		}
	}
	return (1);
}
