/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yechoi <yechoi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 14:17:59 by yechoi            #+#    #+#             */
/*   Updated: 2020/12/20 02:03:24 by yechoi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <errno.h>
# include <signal.h>

# define HUNGRY	0
# define FULL	1
# define DEAD	2

int				g_full_philo_num;
int				g_dead_philo_num;

typedef struct	s_info
{
	int			philo_num;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			must_eat_num;
}				t_info;

typedef struct	s_sems
{
	sem_t		*forks;
	sem_t		*to_write;
	sem_t		*to_check;
}				t_sems;

typedef struct	s_philo
{
	int			idx;
	pid_t		pid;
	t_info		info;
	t_sems		*sems;
	sem_t		*to_eat;
	char		*to_eat_name;
	long		start_time;
	long		last_meal_time;
	int			eaten_meals;
	int			status;
}				t_philo;

/*
** init.c
*/
int				init_info(t_info *info, int argc, char **argv);
int				init_sems(t_info info, t_sems *sems);
t_philo			*init_philos(t_info info, t_sems *sems);

/*
** check.c
*/
int				check_death(t_philo *philo);
int				check_full(t_philo *philo);
void			*check_health(void *p);

/*
** utils.c
*/
int				ft_atoi(const char *nptr);
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
** utils2.c
*/
long			get_time(void);
int				is_digit_str(char *argv);
void			put_message(char *str, t_philo *philo);
char			*ft_strnbrjoin(char *str, int i);

#endif
