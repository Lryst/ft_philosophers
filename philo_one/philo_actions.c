/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:45 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 08:56:44 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int eat_pair(t_philo *philo, int right, int left)
{
	printf("right = %d | left = %d\n", right, left);
	printf("\nBEFORE if PAIR\nLATEST R = %d LATEST L = %d\n", philo->mutex_tab[right]->latest, philo->mutex_tab[left]->latest);
	return (1);
}

int	eat_impair(t_philo *philo, int right, int left)
{
	printf("right = %d | left = %d\n", right, left);
	printf("\nBEFORE if IMPAIR\nLATEST R = %d LATEST L = %d\n", philo->mutex_tab[right]->latest, philo->mutex_tab[left]->latest);
	return (1);
}

int prep_eat(t_philo *philo)
{
	int right;
	int left;

	//exit (1);
	if (philo->i == 0)
	{
		right = philo->i + 1;
		left = 0;
	}
	if (philo->i == philo->nbr - 1)
	{
		right = 0;
		left = philo->nbr - 1;
	}
	else
	{
		right = philo->i + 1;
		left = philo->i;
	}
	//exit (1);
	printf("i = %d | right = %d | left = %d\n", philo->i, right, left);
	if (philo->i % 2 == 0)
		return (eat_pair(philo, right, left));
	if (philo->i % 2 == 1)
		return (eat_impair(philo, right, left));
	return (0);
}

/* 3

				fork 2

		philo 2          philo 1

fork 0                              fork 1

				philo 0 */