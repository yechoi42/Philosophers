/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 01:01:38 by yechoi            #+#    #+#             */
/*   Updated: 2021/02/15 01:32:09 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		exit(1);
		return (1);
	}
	sem_post(philo->to_eat);
	return (0);
}

int		check_full(t_philo *philo)
{
	sem_wait(philo->to_eat);
	if (philo->info.must_eat_num != -1 &&
		philo->eaten_meals >= philo->info.must_eat_num &&
		philo->status != FULL)
	{
		sem_post(philo->to_eat);
		philo->status = FULL;
		sem_post(philo->sems->full);
		return (1);
	}
	sem_post(philo->to_eat);
	return (0);
}

void	*check_health(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	sem_wait(philo->sems->to_check);
	while (philo->status != DEAD)
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

void	*is_full(void *p)
{
	int		count;
	t_philo *philo;

	count = -1;
	philo = (t_philo*)p;
	while (42)
	{
		count++;
		sem_wait(philo->sems->full);
		if (philo->info.must_eat_num != -1 && count == philo->info.philo_num * philo->info.must_eat_num)
		{
			kill(philo->pid, SIGINT);
			break;
		}
	}
	return (NULL);
}