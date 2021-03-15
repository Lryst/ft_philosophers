/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/15 21:20:15 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	philo_think(t_philo *philo)
{
	if (philo->start == 1 && philo->status == 3)
	{
		sem_wait(philo->totem);
		printf("%ldms %d is thinking\n", (get_time() - philo->top), philo->i);
		sem_post(philo->totem);
		philo->status = 1;
	}
}

void	philo_sleep(t_philo *philo)
{
	long	chrono;

	if (philo->start == 1 && philo->status == 2)
	{
		chrono = get_time();
		sem_wait(philo->totem);
		printf("%ldms %d is sleeping\n", (get_time() - philo->top), philo->i);
		sem_post(philo->totem);
		while ((get_time() - chrono) <= philo->sleep)
			;
		philo->status = 3;
	}
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->sem);
	if (philo->start == 1 && philo->status == 1 && philo->turn != 1)
	{
		philo->l_chrono = get_time();
		printf("%ldms %d has taken a fork\n",
		(get_time() - philo->top), philo->i);
		printf("%ldms %d has taken a fork\n",
		(get_time() - philo->top), philo->i);
		printf("%ldms %d is eating\n", (get_time() - philo->top), philo->i);
		philo->r_turn += 1;
		if (philo->r_turn == philo->turn)
			philo->nbr_turn = 1;
		while ((get_time() - philo->l_chrono) <= philo->eat)
			;
		philo->status = 2;
	}
	sem_post(philo->sem);
}
