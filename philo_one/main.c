/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:02:07 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/26 21:30:37 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	put_message(" has taken a fork\n", philo);
	pthread_mutex_lock(philo->right_fork);
	put_message(" has taken a fork\n", philo);
	put_message(" is eating\n", philo);
	pthread_mutex_lock(&philo->to_eat);
	philo->last_meal_time = get_time();
	philo->eaten_meals += 1;
	pthread_mutex_unlock(&philo->to_eat);
	vsleep(philo->info.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*routine(void *p)
{
	pthread_t	monitor;
	t_philo		*philo;

	philo = (t_philo *)p;
	if (philo->idx % 2)
		vsleep(20);
	pthread_create(&monitor, NULL, check_health, p);
	pthread_mutex_lock(philo->to_check);
	while (g_full_philo_num < philo->info.philo_num &&
		g_dead_philo_num == 0)
	{
		pthread_mutex_unlock(philo->to_check);
		eat(philo);
		put_message(" is sleeping\n", philo);
		vsleep(philo->info.time_to_sleep);
		put_message(" is thinking\n", philo);
		pthread_mutex_lock(philo->to_check);
	}
	pthread_mutex_unlock(philo->to_check);
	pthread_detach(monitor);
	return (NULL);
}

void	sit_on_table(t_info info, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < info.philo_num)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
	}
	i = -1;
	while (++i < info.philo_num)
	{
		pthread_join(philos[i].thread, NULL);
	}
}

void	free_destroy(
	t_philo *philos,
	pthread_mutex_t *forks,
	pthread_mutex_t *to_write,
	pthread_mutex_t *to_check
)
{
	int i;

	i = -1;
	while (++i < philos[0].info.philo_num)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].to_eat);
	}
	pthread_mutex_destroy(to_write);
	pthread_mutex_destroy(to_check);
	free(philos);
	free(forks);
}

int		main(int argc, char **argv)
{
	t_info			info;
	t_philo			*philos;
	pthread_mutex_t	to_write;
	pthread_mutex_t	to_check;
	pthread_mutex_t	*forks;

	g_dead_philo_num = 0;
	g_full_philo_num = 0;
	if (argc != 5 && argc != 6)
		return (1);
	if (init_info(&info, argc, argv) == -1)
		return (1);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info.philo_num);
	init_mutexes(info, &to_write, &to_check, forks);
	if (!(philos = init_philos(info, &to_write, &to_check, forks)))
		return (1);
	sit_on_table(info, philos);
	free_destroy(philos, forks, &to_write, &to_check);
	return (0);
}
