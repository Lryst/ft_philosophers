/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:44:31 by lryst             #+#    #+#             */
/*   Updated: 2021/02/28 17:23:26 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct  s_philo
{
    int nbr;
    int die;
    int eat;
    int think;
    int turn;
}               t_philo;


#endif
