/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:27 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 17:21:42 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	test(void *tmp)
{
	t_philo	*philo;
	
	//return ;
	philo = (t_philo*)tmp;
	//printf("philo->i = %d\n", philo->i);
	philo->status = 1;
	philo->top = get_time();
	philo->r_chrono = get_time();
	while (philo->start == 1)
	{
		/* if (philo->turn != -1)
			if (philo->r_turn == philo->turn)
				return; */
		if (philo_eat(philo) == 0)
			philo->start = 0;
		if (philo_sleep(philo) == 0)
			philo->start = 0;
		philo_think(philo);
		if ((get_time() - philo->l_chrono) > philo->life)
			philo->start = 0;
	}
}

int    register_arg(char **av, t_info *info)
{
	info->arg1 = ft_atoi_lite(av[1]);
	info->arg2 = ft_atoi_lite(av[2]);
	info->arg3 = ft_atoi_lite(av[3]);
	info->arg4 = ft_atoi_lite(av[4]);
	if (av[5])
	{
		info->arg5= ft_atoi_lite(av[5]);
		if (info->arg5 == -1)
			return(printf("I don't take a 0 for number of turns arguments, sorry\n"));
	}
	else
		info->arg5 = -1;
	if ((info->arg4 + info->arg3) > info->arg2)
		return (0);
	if ((init_mutex_tab(info)) == 0)
		return (0);
	info->i = 0;
	return (1);
}

int recover_args(char **av)
{
	t_info  info;
	
	if (register_arg(av, &info) != 1)
		return (0);
	if (init_thread_tab(&info) != 1)
		return (0);
	return (1);
}