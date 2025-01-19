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

void	init(t_philo **philo, t_fork **fork, char **argv, struct timeval time)
{
	int	i;
	t_table	*table;
	
	*philo = safe_malloc(ft_atoi(argv[0]) * sizeof(t_philo), "Alloc fail!");
	*fork = safe_malloc(ft_atoi(argv[0]) * sizeof(t_fork), "Fork alloc fail!");
	table = safe_malloc(sizeof(t_table), "Table alloc fail!");
	table->n = ft_atoi(argv[0]);
	table->time_to_die = ft_atoi(argv[1]);
	table->time_to_eat = ft_atoi(argv[2]);
	table->time_to_sleep = ft_atoi(argv[3]);
	if (argv[4])
		table->meals = ft_atoi(argv[4]);
	else
		table->meals = INT_MAX;
	table->fork = *fork;
	i = -1;
	while (++i < ft_atoi(argv[0]))
	{
		(*philo)[i].id = i;
		(*philo)[i].sit = time;
		(*philo)[i].full = false;
		(*philo)[i].last_meal = 0;
		(*fork)[i].fork_id = i;
		if (pthread_mutex_init(&(*fork)[i].mtx, NULL))
			err_msg("Fork mtx init fail!");
		(*philo)[i].table = table;
	}
}
