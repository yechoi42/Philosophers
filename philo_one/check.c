/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:39:20 by yechoi            #+#    #+#             */
/*   Updated: 2021/02/11 23:06:18 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_death(t_philo *philo)
{
	long	now;

	now = get_time();
	pthread_mutex_lock(&philo->to_eat);
	if (now - philo->last_meal_time > philo->info.time_to_die)
	{
		pthread_mutex_unlock(&philo->to_eat);
		put_message(" died\n", philo);
		philo->status = DEAD;
		pthread_mutex_lock(philo->to_check);
		g_dead_philo_num += 1;
		pthread_mutex_unlock(philo->to_check);
		return (1);
	}
	pthread_mutex_unlock(&philo->to_eat);
	return (0);
}

int		check_full(t_philo *philo)
{
	if (philo->info.must_eat_num != -1 &&
		philo->eaten_meals >= philo->info.must_eat_num &&
		philo->status != FULL)
	{
		pthread_mutex_unlock(&philo->to_eat);
		philo->status = FULL;
		pthread_mutex_lock(philo->to_check);
		g_full_philo_num += 1;
		pthread_mutex_unlock(philo->to_check);
		return (1);
	}
	return (0);
}

void	*check_health(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(philo->to_check);
	while (g_full_philo_num < philo->info.philo_num && !g_dead_philo_num)
	{
		pthread_mutex_unlock(philo->to_check);
		if (check_death(philo))
			break ;
		pthread_mutex_lock(&philo->to_eat);
		if (check_full(philo))
			continue ;
		pthread_mutex_unlock(&philo->to_eat);
		pthread_mutex_lock(philo->to_check);
	}
	pthread_mutex_unlock(philo->to_check);
	return (NULL);
}
