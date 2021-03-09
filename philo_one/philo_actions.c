/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 17:21:34 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	philo_think(t_philo *philo)
{
	if (philo->status == 3)
	{
		printf("%ldms %d is thinking\n",(get_time() - philo->top), philo->i);
		philo->status = 1;
	}
}

int	philo_sleep(t_philo *philo)
{
	long	chrono;
	
	chrono = get_time();
	if (philo->status == 2)
	{
		chrono = get_time();
		printf("%ldms %d is sleeping\n",(get_time() - philo->top), philo->i);
		while ((get_time() - chrono) < philo->sleep)
				;
		philo->status = 3;
	}
	return (1);
}

int philo_eat(t_philo *philo)
{
	//exit (1);
	while (philo->mutex_r->latest != philo->i && philo->mutex_l->latest != philo->i && philo->status == 1)
	{
		long	chrono;

		chrono = get_time();
		philo->l_chrono = get_time();
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
		printf("%ldms %d has taken a fork\n",(get_time() - philo->top), philo->i);
		printf("%ldms %d has taken a fork\n",(get_time() - philo->top), philo->i);
		printf("%ldms %d is eating\n",(get_time() - philo->top), philo->i);
		while ((get_time() - chrono) < philo->eat)
				;
		pthread_mutex_unlock(&philo->mutex_l->mutex);
		pthread_mutex_unlock(&philo->mutex_r->mutex);
		philo->r_turn += 1;
		philo->status = 2;
	}
	return (1);
}

/* int prep_eat(t_philo *philo, t_info *info)
{
	int a;
	int b;

	if (philo->i == 0)
	{
		a = philo->i + 1;
		b = 0;
	}
	if (philo->i == philo->nbr - 1)
	{
		a = 0;
		b = philo->nbr - 1;
	}
	else
	{
		a = philo->i + 1;
		b = philo->i;
	}
	if (philo->i % 2 == 0)
		return (eat(philo, a, b, info));
	if (philo->i % 2 == 1)
		return (eat(philo, b, a, info));
	return (0);
} */

/* 3

				fork 2

		philo 2          philo 1

fork 0                              fork 1

				philo 0 */