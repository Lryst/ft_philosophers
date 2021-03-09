/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:48 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 09:02:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_args(char **av)
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

int		start(char **av)
{
	if (check_args(av) == 0)
		return (0);
	if (av[1][0] == '1')
	{
		printf("0ms 1 die\n");
		return (0);
	}
	if (recover_args(av) == 0)
		return (0);
	return (1);
}

int 	main(int ac, char **av)
{
	int i;

	i = 0;
	while (i < 7)
	{
		printf("%d\n", i);
		i++;
	}
	printf("\n");
	if (ac == 5 || ac == 6)
	{
		if (start(av) == 0)
			return (1);
	}
	else
	{	
		write(1, "Bad arguments\n", 14);
	}
	return (0);
}
