/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:21 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/22 17:42:40 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

# define RED "\033[31m"
# define RES "\033[0m"

typedef struct s_fork
{
	pthread_mutex_t	mtx;
	unsigned short	id;
	bool			fork_up;
	struct s_fork	*next;
}			t_fork;

typedef struct s_monitor
{
	struct timeval	sit_time;
	unsigned short	n;
	unsigned short	time_to_die;
	unsigned short	time_to_eat;
	unsigned short	time_to_sleep;
	unsigned short	meals;
	pthread_mutex_t	death_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	meals_mtx;
	bool			end;
}			t_monitor;

typedef struct s_philo
{
	pthread_t		thread;
	t_fork			*right_fork;
	t_fork			*left_fork;
	unsigned short	id;
	unsigned short	meals_eaten;
	unsigned long	last_meal_time;
	t_monitor		*monitor;
	bool			full;
}			t_philo;

void	is_valid_integer(char **arr);
int		ft_atoi(char *str);
long	timer(struct timeval start);
void	end_setter(t_monitor *monitor);
bool	end_getter(t_monitor *monitor);
void	init_data(t_philo **philo, t_fork **fork, t_monitor **mon, char **argv);
void	dinner(t_philo **philo, t_monitor **monitor);
void	safe_free(t_philo *philo);


void	print_monitor(t_monitor monitor);
void	activity(long milliseconds, t_monitor *monitor);
void	custom_print(t_philo *philo, char *msg);
bool	philo_check(t_philo *philo);

#endif
