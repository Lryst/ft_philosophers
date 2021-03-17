/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/17 11:36:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		philo_think(t_philo *philo)
{
	if (philo->status == 3)
	{
		print((get_time() - philo->top), philo->i, "is thinking", philo->totem);
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
		print((get_time() - philo->top), philo->i, "is sleeping", philo->totem);
		while ((get_time() - chrono) <= philo->sleep)
			;
		philo->status = 3;
	}
	return (0);
}

int		philo_eat(t_philo *philo)
{
	sem_wait(philo->sem);
	if (philo->status == 1 && philo->nbr_turn != 1)
	{
		philo->l_chrono = get_time();
		print((get_time() - philo->top), philo->i, "has taken a fork", philo->totem);
		print((get_time() - philo->top), philo->i, "has taken a fork", philo->totem);
		print((get_time() - philo->top), philo->i, "is eating", philo->totem);
		philo->r_turn += 1;
		if (philo->r_turn == philo->turn)
			philo->nbr_turn = 1;
		while ((get_time() - philo->l_chrono) <= philo->eat)
			;
		philo->status = 2;
	}
	sem_post(philo->sem);
	return (0);
}
