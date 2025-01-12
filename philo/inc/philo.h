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

typedef struct s_philo
{
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	pthread_mutex_t	last_meal_mtx;
	struct timeval	sit;
	unsigned int	id;
	unsigned int	meals;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	long			last_meal;
	bool			finish;
	struct s_philo	*next_philo;
}			t_philo;

typedef struct s_table
{
	t_philo		*philo;
	pthread_t	monitor;
	int			n;
	int			finished_meals;
}			t_table;

void	is_valid_integer(char **arr);
int		ft_atoi(const char *str);
long	timer(struct timeval start);
void	table_init(t_philo **head, t_table *table, char **params, struct timeval start);
void	*routine(void *args);
void	safe_free(t_philo *philo, t_table table);

#endif