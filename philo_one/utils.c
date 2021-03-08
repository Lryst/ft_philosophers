/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:08:59 by lryst             #+#    #+#             */
/*   Updated: 2021/03/07 21:53:47 by lryst            ###   ########.fr       */
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

void		print_values_chrono(long chrono)
{
	printf("%ldms\n", get_time() - chrono);
}

int		ft_atoi_lite(char *str)
{
	int i;
	int nbr;

	i = -1;
	nbr = 0;
	if (str[i] == '-')
		return (-1);
	while (str[++i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		nbr = (nbr * 10) + (int)(str[i] - '0');
	}
	if (nbr == 0)
		return (-1);
	printf("		ATOI %d\n", nbr);
	return (nbr);
}

int		monitor(t_info *info)
{
	int		i;
	long	chrono;
	
	i = 0;
	chrono = get_time();
	while (1)
	{
		i = 0;
		while (info->philo[i])
		{
			//write(1, "coucou\n", 7);
			if (info->philo[i]->start == 0)
			{
				printf("%ldms philo %d die\n",(get_time() - chrono), i);
				//pthread_detach(philo[i]->thread);
				i = 0;
				while (info->philo[i])
				{
					//write(1, "coucou\n", 7);
					info->philo[i++]->start = 0;
					//pthread_detach(philo[i]->thread);
				}
				return(0) ;
			}
			i++;
		}
	}
	return (1);
}

int     free_mutex_tab(t_mutex **mutex_tab)
{
	int i;

	i = 0;
	if (mutex_tab)
	{
		while (mutex_tab[i])
		{
			pthread_mutex_destroy(&mutex_tab[i]->mutex);
			i++;
		}
		free(mutex_tab);
		mutex_tab = NULL;
	}
	return (0);
}
