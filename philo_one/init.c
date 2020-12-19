/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:38:03 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/20 00:38:31 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     init_info(t_info *info, int argc, char **argv)
{
    int i;

    i = 0;
    while (++i < argc)
    {
        if (is_digit_str(argv[i]) == -1)
            return (-1);
    }
    info->philo_num = ft_atoi(argv[1]);
    if (info->philo_num <= 2)
        return (-1);
    info->time_to_die = ft_atoi(argv[2]);
    info->time_to_eat = ft_atoi(argv[3]) * 1000;
    info->time_to_sleep = ft_atoi(argv[4]) * 1000;
    if (argc == 6)
        info->must_eat_num = ft_atoi(argv[5]);
    else
        info->must_eat_num = -1;
    return (0);
}

void     init_mutexes(
    t_info info,
    pthread_mutex_t *to_write,
    pthread_mutex_t *to_check,
    pthread_mutex_t *forks
    )
{
    int i;

    i = -1;
    while (++i < info.philo_num)
    {
        pthread_mutex_init(&(forks[i]), NULL);
    }
    pthread_mutex_init(to_write, NULL);
    pthread_mutex_init(to_check, NULL);
}

t_philo *init_philos(
    t_info info,
    pthread_mutex_t *to_write,
    pthread_mutex_t *to_check,
    pthread_mutex_t *forks
    )
{
    int     i;
    t_philo *philos;

    if (!(philos = (t_philo *)malloc(sizeof(t_philo) * info.philo_num)))
        return (NULL);
    i = -1;
    while (++i < info.philo_num)
    {
        philos[i].idx = i;
        philos[i].info = info;
        philos[i].left_fork = &forks[i];
        if (i == info.philo_num - 1)
            philos[i].right_fork = &forks[0];
        else
            philos[i].right_fork = &forks[i + 1];
        philos[i].to_write = to_write;
        philos[i].to_check = to_check;
        pthread_mutex_init(&philos[i].to_eat, NULL);
        philos[i].start_time = get_time();
        philos[i].last_meal_time = get_time();
        philos[i].eaten_meals = 0;
        philos[i].status = HUNGRY;
    }
    return (philos);
}
