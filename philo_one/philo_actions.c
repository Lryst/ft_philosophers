/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/25 08:26:25 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_think(t_philo *philo)
{
	if (philo->status == 3)
	{
		pthread_mutex_lock(philo->totem);
		printf("%ldms %d is thinking\n", (get_time() - philo->top),
		philo->i + 1);
		pthread_mutex_unlock(philo->totem);
		philo->status = 1;
	}
}

void	philo_sleep(t_philo *philo)
{
	long	chrono;

	chrono = get_time();
	if (philo->status == 2)
	{
		pthread_mutex_lock(philo->totem);
		printf("%ldms %d is sleeping\n", (get_time() - philo->top),
		philo->i + 1);
		pthread_mutex_unlock(philo->totem);
		while ((get_time() - chrono) < philo->sleep)
			usleep(10);
		philo->status = 3;
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->i % 2 == 0)
	{
		pthread_mutex_lock(&philo->mutex_r->mutex);
		pthread_mutex_lock(&philo->mutex_l->mutex);
		philo->mutex_r->latest = philo->i;
		philo->mutex_l->latest = philo->i;
	}
	if (philo->i % 2 == 1)
	{
		pthread_mutex_lock(&philo->mutex_l->mutex);
		pthread_mutex_lock(&philo->mutex_r->mutex);
		philo->mutex_l->latest = philo->i;
		philo->mutex_r->latest = philo->i;
	}
}

void	philo_eat(t_philo *philo)
{
	if (philo->mutex_r->latest != philo->i &&
		philo->mutex_l->latest != philo->i && philo->status == 1 &&
		philo->nbr_turn != 1)
	{
		take_fork(philo);
		philo->l_chrono = get_time();
		pthread_mutex_lock(philo->totem);
		printf("%ldms %d has taken a fork\n",
		(get_time() - philo->top), philo->i + 1);
		printf("%ldms %d has taken a fork\n",
		(get_time() - philo->top), philo->i + 1);
		printf("%ldms %d is eating\n", (get_time() - philo->top), philo->i + 1);
		pthread_mutex_unlock(philo->totem);
		philo->r_turn += 1;
		if (philo->r_turn == philo->turn)
			philo->nbr_turn = 1;
		while ((get_time() - philo->l_chrono) < philo->eat)
			usleep(10);
		pthread_mutex_unlock(&philo->mutex_l->mutex);
		pthread_mutex_unlock(&philo->mutex_r->mutex);
		philo->status = 2;
	}
}
