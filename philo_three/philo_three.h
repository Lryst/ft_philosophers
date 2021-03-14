/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:20:39 by lryst             #+#    #+#             */
/*   Updated: 2021/03/14 21:59:01 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct		s_philo
{
	int				pid;
	int				id;
	int				r_turn;
	int				nbr;
	long			life;
	long			sleep;
	long			eat;
	int				start;
	int				i;
	int				turn;
	long			top;
	long			r_chrono;
	long			l_chrono;
	int				status;
	int				nbr_turn;
	sem_t			*sem;
	sem_t			*totem;
}					t_philo;

typedef struct		s_info
{
	int				arg1;
	long			arg2;
	long			arg3;
	long			arg4;
	int				arg5;
	int				i;
	long			top_chrono;
	sem_t			*sem;
	sem_t			*totem;
	t_philo			*philo;
}					t_info;

/*
** init.c
*/
void				lauch_philo(t_info *info, int i);
void				init_philo_param(t_info *info, t_philo *philo);
int					init_thread_tab(t_info *info);

/*
** main.c
*/
int					check_args(char **av);
int					start(char **av);
int					main(int ac, char **av);

/*
** philo_actions.c
*/
void				philo_think(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);

/*
** philo_routine.c
*/
int					recover_args(char **av);
int					test(t_philo *philo);

/*
** utils.c
*/
long				get_time(void);
int					ft_atoi_lite(char *str);
int					monitor_check_count_meal(t_info *info);
int					philo_die(t_info *info, int i);
int					monitor(t_info *info);

#endif
