/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:40:05 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/26 21:25:42 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	vsleep(long time)
{
	long	start_time;
	long	now;

	start_time = get_time();
	while (42)
	{
		now = get_time();
		if (now - start_time > time)
			return;
		usleep(100);
	}
}

long	get_time(void)
{
	struct timeval mytime;

	gettimeofday(&mytime, NULL);
	return (mytime.tv_sec * 1000L + mytime.tv_usec / 1000L);
}

int		is_digit_str(char *argv)
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

void	put_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->to_write);
	pthread_mutex_lock(philo->to_check);
	if (g_full_philo_num < philo->info.philo_num &&
		g_dead_philo_num == 0)
	{
		pthread_mutex_unlock(philo->to_check);
		ft_putnbr_fd(get_time() - philo->start_time, 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo->idx, 1);
		ft_putstr_fd(str, 1);
		pthread_mutex_unlock(philo->to_write);
		return ;
	}
	pthread_mutex_unlock(philo->to_write);
	pthread_mutex_unlock(philo->to_check);
}
