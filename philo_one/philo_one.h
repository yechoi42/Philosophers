/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 20:02:19 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/26 21:29:44 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

# define HUNGRY		0
# define FULL		1
# define DEAD		2

int					g_full_philo_num;
int					g_dead_philo_num;

typedef struct		s_info
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_num;
}					t_info;

typedef struct		s_philo
{
	int				idx;
	pthread_t		thread;
	t_info			info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*to_write;
	pthread_mutex_t	*to_check;
	pthread_mutex_t	to_eat;
	long			start_time;
	long			last_meal_time;
	int				eaten_meals;
	int				status;
}					t_philo;

/*
** init.c
*/
int					init_info(t_info *info, int argc, char **argv);
void				init_mutexes(t_info info, pthread_mutex_t *to_write,
		pthread_mutex_t *to_check, pthread_mutex_t *forks);
t_philo				*init_philos(t_info info, pthread_mutex_t *to_write,
		pthread_mutex_t *to_check, pthread_mutex_t *forks);

/*
** check.c
*/
int					check_death(t_philo *philo);
int					check_full(t_philo *philo);
void				*check_health(void *p);

/*
** utils.c
*/
int					ft_atoi(const char *nptr);
size_t				ft_strlen(const char *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

/*
** utils2.c
*/
void				vsleep(long time);
long				get_time();
int					is_digit_str(char *argv);
void				put_message(char *str, t_philo *philo);

#endif
