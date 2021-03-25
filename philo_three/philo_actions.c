/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/25 08:26:54 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		philo_think(t_philo *philo)
{
	if (philo->status == 3)
	{
		if (philo->nbr_turn != 1 && (get_time() - (philo->l_chrono)) >
			philo->life)
		{
			philo->start = 1;
			return (1);
		}
		print((get_time() - philo->top), "is thinking", philo);
		philo->status = 1;
	}
	return (0);
}

int		philo_sleep(t_philo *philo)
{
	long	chrono;

	chrono = get_time();
	if (philo->status == 2)
	{
		if (philo->nbr_turn != 1 && (get_time() - (philo->l_chrono)) >
			philo->life)
		{
			philo->start = 1;
			return (1);
		}
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
		if (philo->nbr_turn != 1 && (get_time() - (philo->l_chrono)) >
			philo->life)
		{
			philo->start = 1;
			return (1);
		}
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
