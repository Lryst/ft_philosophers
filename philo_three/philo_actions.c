/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/16 12:35:35 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		philo_think(t_philo *philo)
{
	while (philo->status == 3)
	{
		printf("%ldms %d is thinking\n", (get_time() - philo->top), philo->i);
		philo->status = 1;
	}
	return (0);
}

int		philo_sleep(t_philo *philo)
{
	long	chrono;

	while (philo->status == 2)
	{
		chrono = get_time();
		printf("%ldms %d is sleeping\n", (get_time() - philo->top), philo->i);
		while ((get_time() - chrono) <= philo->sleep)
			;
		philo->status = 3;
	}
	return (0);
}

int		philo_eat(t_philo *philo)
{
	sem_wait(philo->sem);
	while (philo->status == 1 && philo->turn != 1)
	{
		//sem_wait(philo->sem);
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
		//sem_post(philo->sem);
		philo->status = 2;
	}
	sem_post(philo->sem);
	return (0);
}
