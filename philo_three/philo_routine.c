/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:27 by lryst             #+#    #+#             */
/*   Updated: 2021/03/19 14:01:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
