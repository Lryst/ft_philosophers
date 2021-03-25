/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:59 by lryst             #+#    #+#             */
/*   Updated: 2021/03/22 20:28:25 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	print(long time, char *str, t_philo *philo)
{
	sem_wait(*philo->totem);
	printf("%ldms %d %s\n", time, philo->i + 1, str);
	sem_post(*philo->totem);
}

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

void	monitor(void *tmp)
{
	t_philo *philo;

	philo = (t_philo*)tmp;
	while (1)
	{
		usleep(20);
		if (philo->nbr_turn == 1)
			break ;
		if (philo->nbr_turn != 1 && (get_time() - (philo->l_chrono)) >
			philo->life)
		{
			philo->start = 1;
			sem_wait(*philo->totem);
			printf("%ldms %d died\n", (get_time() - philo->top), philo->i + 1);
			break ;
		}
	}
}
