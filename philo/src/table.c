/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 13:14:27 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*safe_malloc(size_t size, char *msg)
{
	void	*arg;

	arg = malloc(size);
	if (!arg)
		err_msg(msg);
	return (arg);
}

void	init(t_philo **philo, char **argv, struct timeval time)
{
	int	i;
	t_table	*table;
	
	*philo = safe_malloc(ft_atoi(argv[0]) * sizeof(t_philo), "Alloc failed!");
	table = safe_malloc(sizeof(t_table), "Table alloc failed");
	table->n = ft_atoi(argv[0]);
	table->time_to_die = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		table->meals = ft_atoi(argv[4]);
	else
		table->meals = INT_MAX;
	i = -1;
	while (++i < ft_atoi(argv[0]))
	{
		(*philo)[i].id = i;
		(*philo)[i].sit = time;
		(*philo)[i].full = false;
		(*philo)[i].last_meal = 0;
		(*philo)[i].table = table;
		(*philo)[i].fork = safe_malloc(sizeof(t_fork), "Fork alloc failed!");
		(*philo)[i].fork->fork_id = i;
		pthread_mutex_init(&(*philo)[i].fork->mtx, NULL);
	}
}
