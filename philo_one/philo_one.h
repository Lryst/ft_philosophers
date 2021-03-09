/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 19:09:13 by lryst             #+#    #+#             */
/*   Updated: 2021/03/09 08:38:40 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef	struct	s_mutex
{
	pthread_mutex_t	mutex;
	int				latest;
}				t_mutex;

typedef struct  s_philo
{
    pthread_t   thread;
    t_mutex     **mutex_tab;
    int         r_turn;
    int         nbr;
    long        life;
    long        sleep;
    long        eat;
    int         start;
    int         i;
    int         turn;
    long        start_chrono;
}               t_philo;

typedef struct  s_info
{
    int         arg1;
    long        arg2;
    long        arg3;
    long        arg4;
    int         arg5;
    int         i;
    t_mutex     **mutex_tab;
    t_philo     **philo;
    pthread_mutex_t totem;
}               t_info;

/*
** init.c
*/
int		init_mutex_tab(t_mutex **mutex_tab, int len);
int     init_philo_param(t_info *info, t_philo *philo);
int     init_thread_tab(t_info *info);

/*
** main.c
*/
int		check_args(char **av);
int		start(char **av);
int 	main(int ac, char **av);

/*
** philo_actions.c
*/
int eat_pair(t_philo *philo, int right, int left);
int	eat_impair(t_philo *philo, int right, int left);
int prep_eat(t_philo *philo);

/*
** philo_routine.c
*/
int recover_args(char **av);
void	test(t_info *info);


/*
** utils.c
*/
long	get_time(void);
void	print_values_chrono(long chrono);
//void	print_values_philo(t_philo *philo);
int		ft_atoi_lite(char *str);
int		monitor(t_info *info);
int     free_mutex_tab(t_mutex **mutex_tab);

#endif