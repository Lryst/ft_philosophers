/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:27 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 09:12:12 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	test(t_info *info)
{
	t_philo	philo;
//printf("\nSTRUCT\ni = %d\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", philo->i, philo->nbr, philo->life, philo->eat, philo->sleep);
	//printf("\nSTRUCT\ni = %d\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->i, info->arg1, info->arg2, info->arg3, info->arg4);
	init_philo_param(info, &philo);
	printf("\nPHILO STRUCT\ni = %d\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", philo.i, philo.nbr, philo.life, philo.eat, philo.sleep);
	//exit (1);
	while (1)
	{
		//exit(1);
		//printf("\nSTRUCT\ni = %d\nnbr = %d\nlife = %ld\neat = %ld\nsleep = %ld\n", info->i, info->arg1, info->arg2, info->arg3, info->arg4);
		printf("loop index = %d\n", philo.i);
		printf("philo number %d\n", philo.i);
		//exit (1);
		if (prep_eat(&philo) == 0)
			printf("we have a probleme with philo_actions\n");
		return ;
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
	{
		info->arg5 = -1;
	}
	info->i = 0;
	/* if ((init_mutex_tab(info->mutex_tab, info->arg1)) == 0)
		return (free_mutex_tab(info->mutex_tab)); */
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