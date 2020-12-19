/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:41:38 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/20 01:35:04 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		check_death(t_philo *philo)
{
	long now;

	now = get_time();
	sem_wait(philo->to_eat);
	if (now - philo->last_meal_time > philo->info.time_to_die)
	{
		sem_post(philo->to_eat);
		put_message(" died\n", philo);
		philo->status = DEAD;
		sem_wait(philo->sems->to_check);
		g_dead_philo_num += 1;
		sem_post(philo->sems->to_check);
		return (1);
	}
	sem_post(philo->to_eat);
	return (0);
}

int		check_full(t_philo *philo)
{
	sem_wait(philo->to_eat);
	if (philo->info.must_eat_num != -1 &&
		philo->eaten_meals >= philo->info.must_eat_num)
	{
		sem_post(philo->to_eat);
		philo->status = FULL;
		sem_wait(philo->sems->to_check);
		g_full_philo_num += 1;
		sem_post(philo->sems->to_check);
		return (1);
	}
	sem_post(philo->to_eat);
	return (0);
}

void	*check_health(void *p)
{
	t_philo *philo;

	philo = (t_philo *)p;
	sem_wait(philo->sems->to_check);
	while (g_full_philo_num < philo->info.philo_num && !g_dead_philo_num)
	{
		sem_post(philo->sems->to_check);
		if (check_death(philo))
			break ;
		check_full(philo);
		sem_wait(philo->sems->to_check);
	}
	sem_post(philo->sems->to_check);
	return (NULL);
}
