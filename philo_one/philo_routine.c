/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:27 by lryst             #+#    #+#             */
/*   Updated: 2021/03/20 20:48:07 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	test(void *tmp)
{
	t_philo	*philo;

	philo = (t_philo*)tmp;
	philo->status = 1;
	philo->top = get_time();
	philo->nbr_turn = 0;
	philo->l_chrono = get_time();
	while (philo->start == 1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}

int		register_arg(char **av, t_info *info)
{
	if (info->arg1 == -1 || info->arg2 == -1 ||
		info->arg3 == -1 || info->arg4 == -1)
		return (0);
	if (av[5])
	{
		info->arg5 = ft_atoi_lite(av[5]);
		if (info->arg5 == -1)
			return (write(1, "I don't take 0 for number of meal, sorry\n", 41));
	}
	else
		info->arg5 = -1;
	if ((info->arg4 + info->arg3) > info->arg2)
		return (0);
	if ((init_mutex_tab(info)) == 0)
		return (0);
	pthread_mutex_init(&info->totem, NULL);
	info->i = 0;
	return (1);
}

int		recover_args(char **av)
{
	t_info	info;

	info.arg1 = ft_atoi_lite(av[1]);
	info.arg2 = ft_atoi_lite(av[2]);
	info.arg3 = ft_atoi_lite(av[3]);
	info.arg4 = ft_atoi_lite(av[4]);
	if (register_arg(av, &info) != 1)
		return (0);
	if (init_thread_tab(&info) != 1)
		return (0);
	return (1);
}
