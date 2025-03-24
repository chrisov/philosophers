/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:21 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/24 20:29:58 by dchrysov         ###   ########.fr       */
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
	unsigned short	id;
	unsigned short	meals_eaten;
	unsigned long	last_meal_time;
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_monitor		*monitor;
	bool			full;
}			t_philo;

int		ft_atoi(char *str);
int		meal_counter(t_philo *philo, t_monitor *mon, int *meal_num);
long	timer(struct timeval start);
bool	forks_pickup(t_philo *philo);
bool	uwait(long milliseconds, t_monitor **monitor);
bool	custom_print(t_philo *philo, char *msg);
bool	bool_getter(bool *var, pthread_mutex_t *mutex);
void	bool_setter(bool *var, bool value, pthread_mutex_t *mutex);
void	is_valid_integer(char *str);
void	*forks_down(t_philo *philo);
void	init_data(t_philo **philo, t_fork **fork, t_monitor **mon, char **argv);
void	dinner(t_philo **philo, t_monitor **monitor);
void	join_n_free(t_philo **philo, t_monitor **monitor, t_fork **fork_node);
void	*forks_down(t_philo *philo);
bool	forks_pickup(t_philo *philo);

#endif
