/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 21:17:45 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/26 21:30:58 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eat(t_philo *philo)
{
	if (philo->status == DEAD)
		return (1);
	sem_wait(philo->sems->forks);
	put_message(" has taken a fork\n", philo);
	sem_wait(philo->sems->forks);
	put_message(" has taken a fork\n", philo);
	if (philo->status != DEAD)
	{
		put_message(" is eating\n", philo);
		sem_wait(philo->to_eat);
		philo->last_meal_time = get_time();
		philo->eaten_meals += 1;
		sem_post(philo->to_eat);
		vsleep(philo->info.time_to_eat);
	}
	sem_post(philo->sems->forks);
	sem_post(philo->sems->forks);
	return (0);
}

void	*routine(void *p)
{
	pthread_t	monitor;
	t_philo		*philo;

	philo = (t_philo *)p;
	if (philo->idx % 2)
		vsleep(philo->info.time_to_eat);
	pthread_create(&monitor, NULL, check_health, p);
	sem_wait(philo->sems->to_check);
	while (g_full_philo_num < philo->info.philo_num &&
		g_dead_philo_num == 0)
	{
		sem_post(philo->sems->to_check);
		eat(philo);
		put_message(" is sleeping\n", philo);
		vsleep(philo->info.time_to_sleep);
		put_message(" is thinking\n", philo);
		sem_wait(philo->sems->to_check);
	}
	sem_post(philo->sems->to_check);
	pthread_detach(monitor);
	return (NULL);
}

void	sit_on_table(t_info info, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < info.philo_num)
	{
		if ((philos[i].pid = fork()) == -1)
			return ;
		else if (philos[i].pid == 0)
		{
			routine(&philos[i]);
		}
	}
	return ;
}

void	free_destroy(t_info info, t_philo *philos, t_sems *sems)
{
	int i;

	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < info.philo_num)
	{
		kill(philos[i].pid, SIGINT);
	}
	i = -1;
	while (++i < info.philo_num)
	{
		sem_close(philos[i].to_eat);
		sem_unlink(philos[i].to_eat_name);
		free(philos[i].to_eat_name);
	}
	sem_close(sems->forks);
	sem_close(sems->to_check);
	sem_close(sems->to_write);
	sem_unlink("/forks");
	sem_unlink("/to_write");
	sem_unlink("/to_check");
}

int		main(int argc, char **argv)
{
	t_info		info;
	t_philo		*philos;
	t_sems		sems;

	g_dead_philo_num = 0;
	g_full_philo_num = 0;
	if (argc != 5 && argc != 6)
		return (1);
	if (init_info(&info, argc, argv) == -1)
		return (1);
	if (init_sems(info, &sems) == -1)
		return (1);
	if (!(philos = init_philos(info, &sems)))
		return (1);
	init_sems(info, &sems);
	sit_on_table(info, philos);
	free_destroy(info, philos, &sems);
}
