/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:44:43 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/20 00:45:39 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

long    get_time()
{
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    return (mytime.tv_sec * 1000L + mytime.tv_usec / 1000L);
}

int     is_digit_str(char *argv)
{
    int i;

    i = -1;
    while (argv[++i])
    {
        if (argv[i] < '0' || argv[i] > '9')
            return (-1);
    }
    return (0);
}

char    *ft_strnbrjoin(char *str, int i)
{
    int     i2;
    int     str_len;
    int     int_len;
    char    *ret;

    i2 = i;
    int_len = 0;
    while(i2 > 0)
    {
        i2 /= 10;
        int_len++;
    }
    str_len = ft_strlen(str);
    ret = (char *)malloc(sizeof(char) * (int_len + str_len + 1));
    memcpy(ret, str, str_len);
    ret[int_len + str_len] = '\0';
    while (--int_len >= 0)
    {
        ret[str_len + int_len] = 48 + i % 10;
        i /= 10;
    }
    return (ret);
}

void    put_message(char *str, t_philo *philo)
{
    long now;

    now = 0;
    sem_wait(philo->sems->to_check);
    if (g_full_philo_num < philo->info.philo_num &&
        g_dead_philo_num == 0)
    {
        sem_post(philo->sems->to_check);
        sem_wait(philo->sems->to_write);
        now = get_time();
        ft_putnbr_fd(now - philo->start_time, 1);
        ft_putstr_fd(" ", 1);
        ft_putnbr_fd(philo->idx, 1);
        ft_putstr_fd(str, 1);
        sem_post(philo->sems->to_write);
        return;
    }
    sem_post(philo->sems->to_check);
}