≠/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:22:01 by lryst             #+#    #+#             */
/*   Updated: 2021/02/28 17:23:04 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	get_time(void)
{
	struct timeval tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}

void		print_values(long chrono, t_philo *philo)
{
	printf("%ldms\n", get_time() - chrono);
	if (philo)
		;
	printf("struct =>\nnbr [%d]\ndie [%d]\neat [%d]\nthink [%d]\nturn [%d]\n", philo->nbr, philo->die, philo->eat, philo->think, philo->turn);
}

int		ft_atoi_lite(char *str)
{
	int i;
	int nbr;

	i = -1;
	nbr = 0;
	//printf("\nstr = [%s]\n", str);
	if (str[i] == '-')
		return (-1);
	while (str[++i])
		nbr = (nbr * 10) + (int)(str[i] - '0');
	if (nbr == 0)
		return (-1);
	return (nbr);
}

int		recover_args(t_philo *philo, char **av)
{
	philo->nbr = -1;
    philo->die = -1;
    philo->eat = -1;
    philo->think = -1;
	philo->turn = -2;

	philo->nbr = ft_atoi_lite(av[1]);
	philo->die = ft_atoi_lite(av[2]);
	philo->eat = ft_atoi_lite(av[3]);
	philo->think = ft_atoi_lite(av[4]);
	if (av[5])
		philo->turn = ft_atoi_lite(av[5]);
	if ((philo->nbr == -1) ||
		(philo->die == -1) ||
		(philo->eat == -1) ||
		(philo->think == -1) ||
		(av[5] && (philo->turn == -1)))
		return (0);
	return (1);
}

int 	start(char **av, t_philo *philo)
{
	long chrono;

	chrono = get_time();
	if (recover_args(philo,av) == 0)
		return (0);
	print_values(chrono, philo);
	return (1);
}

int 	main(int ac, char **av)
{
	t_philo philo;
	if (ac)
		;
	if (ac == 5 || ac == 6)
		if (start(av, &philo) != 0)
			return (1);
	write(1, "Bad arguments\n", 14);
	return (0);
}
