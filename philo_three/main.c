/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:48 by lryst             #+#    #+#             */
/*   Updated: 2021/03/17 11:36:32 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	check_args(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || 57 < av[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	start(char **av)
{
	int	arg1;

	arg1 = ft_atoi_lite(av[1]);
	if (check_args(av) == 0)
		return (0);
	if (arg1 == 1)
	{
		write(1, "0ms 1 die\n", 10);
		return (0);
	}
	if (recover_args(av) == 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (start(av) == 0)
			return (write(1, "We have a probleme !\n", 21));
	}
	else
		write(1, "Bad arguments\n", 14);
	return (0);
}
