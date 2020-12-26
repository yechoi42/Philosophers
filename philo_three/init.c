/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 00:45:54 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/26 21:55:20 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_info(t_info *info, int argc, char **argv)
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
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->must_eat_num = ft_atoi(argv[5]);
	else
		info->must_eat_num = -1;
	return (0);
}

int		init_sems(t_info info, t_sems *sems)
{
	sem_unlink("/forks");
	sem_unlink("/to_write");
	sem_unlink("/to_check");
	if ((sems->forks = sem_open("/forks", O_CREAT | O_EXCL,
					0644, info.philo_num)) == SEM_FAILED)
		return (-1);
	if ((sems->to_write = sem_open("/to_write", O_CREAT | O_EXCL,
					0644, 1)) == SEM_FAILED)
		return (-1);
	if ((sems->to_check = sem_open("/to_check", O_CREAT | O_EXCL,
					0644, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

t_philo	*init_philos(t_info info, t_sems *sems)
{
	int		i;
	t_philo	*philos;

	if (!(philos = (t_philo *)malloc(sizeof(t_philo) * info.philo_num)))
		return (NULL);
	i = -1;
	while (++i < info.philo_num)
	{
		philos[i].idx = i;
		philos[i].info = info;
		philos[i].sems = sems;
		philos[i].to_eat_name = ft_strnbrjoin("/to_eat", i);
		sem_unlink(philos[i].to_eat_name);
		if ((philos[i].to_eat = sem_open(philos[i].to_eat_name,
			O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
			return (NULL);
		philos[i].start_time = get_time();
		philos[i].last_meal_time = get_time();
		philos[i].eaten_meals = 0;
		philos[i].status = HUNGRY;
	}
	return (philos);
}
