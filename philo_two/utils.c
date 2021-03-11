/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:59 by lryst             #+#    #+#             */
/*   Updated: 2021/03/11 14:12:34 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int		monitor(t_info *info)
{
	int		i;
	long	chrono;

	chrono = get_time();
	while (1)
	{
		i = 0;
		while (i < info->arg1)
		{
			if (info->philo[i].nbr_turn == 1)
				if (monitor_check_count_meal(info) == 1)
					return (1);
			if (info->philo[i].start == 0)
			{
				printf("MOUHAHA %ldms philo %d die\n", (get_time() - chrono), i);
				i = 0;
				while (i < info->arg1)
					info->philo[i++].start = 0;
				return (0);
			}
			i++;
		}
	}
	return (1);
}
