/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/25 08:26:16 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	print(long time, char *str, t_philo *philo)
{
	sem_wait(*philo->totem);
	printf("%ldms %d %s\n", time, philo->i + 1, str);
	sem_post(*philo->totem);
}

int		philo_think(t_philo *philo)
{
	if (philo->status == 3)
	{
		print((get_time() - philo->top), "is thinking", philo);
		philo->status = 1;
	}
	return (0);
}

int		philo_sleep(t_philo *philo)
{
	long	chrono;

	if (philo->status == 2)
	{
		chrono = get_time();
		print((get_time() - philo->top), "is sleeping", philo);
		while ((get_time() - chrono) < philo->sleep)
			usleep(10);
		philo->status = 3;
	}
	return (0);
}

int		philo_eat(t_philo *philo)
{
	sem_wait(*philo->sem);
	if (philo->status == 1 && philo->nbr_turn != 1)
	{
		philo->l_chrono = get_time();
		print((get_time() - philo->top), "has taken a fork", philo);
		print((get_time() - philo->top), "has taken a fork", philo);
		print((get_time() - philo->top), "is eating", philo);
		philo->r_turn += 1;
		if (philo->r_turn == philo->turn)
			philo->nbr_turn = 1;
		while ((get_time() - philo->l_chrono) < philo->eat)
			usleep(10);
		philo->status = 2;
	}
	sem_post(*philo->sem);
	return (0);
}
