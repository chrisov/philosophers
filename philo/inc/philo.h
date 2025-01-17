/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:21 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/08 12:33:43 by dchrysov         ###   ########.fr       */
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

# define RED "\033[1;31m"
# define RES "\033[0m"

typedef	struct s_fork
{
	pthread_mutex_t	mtx;
	int				fork_id;
}			t_fork;

typedef struct s_table
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	last_meal_mtx;
	pthread_t		monitor;
	int				n;
	unsigned int	meals;
}			t_table;

typedef struct s_philo
{
	pthread_t		thread_id;
	struct timeval	sit;
	int				id;
	int				last_meal;
	int				meals_eaten;
	bool			full;
	t_fork			fork;
	t_table			*table;
}			t_philo;

void	is_valid_integer(char **arr);
int		ft_atoi(const char *str);
long	timer(struct timeval start);
void	init(t_philo **philo, t_fork **fork, char **argv, struct timeval time);

#endif