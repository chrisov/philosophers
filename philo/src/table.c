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
	{
		perror(msg);
		exit (EXIT_FAILURE);
	}
	return (arg);
}

/**
 * @brief Initializes i = argv[0] number of forks as a circular linked list.
 *
 * @note Edge case where argv[0] = 1!
 */
static t_fork	*forks_init(char *param)
{
	t_fork	*fork;
	t_fork	*current;
	int	i;

	i = 1;
	fork = safe_malloc(sizeof(t_fork), "Error allocating fork");
	fork->id = i;
	if (pthread_mutex_init(&fork->mtx, NULL) != 0)
		return(printf("Mutex init failed\n"), NULL);
	current = fork;
	while (++i < ft_atoi(param) + 1)
	{
		current->next = safe_malloc(sizeof(t_fork), "Error allocating fork");
		current = current->next;
		current->id = i;
		if (pthread_mutex_init(&current->mtx, NULL) != 0)
			return(printf("Fork mutex init failed\n"), NULL);
		current->next = NULL;
	}
	current->next = fork;
	return (fork);
}

/**
 * @brief Init monitor with program's params and the philo list.
 */
static t_monitor	*monitor_init(char **param, struct timeval time)
{
	t_monitor	*monitor;

	monitor = safe_malloc(sizeof(t_monitor), "Error allocating monitor");
	monitor->n = ft_atoi(param[0]);
	monitor->sit_time = time;
	monitor->time_to_die = ft_atoi(param[1]);
	monitor->time_to_eat = ft_atoi(param[2]);
	monitor->time_to_sleep = ft_atoi(param[3]);
	if (param[4])
		monitor->meals = ft_atoi(param[4]);
	else
		monitor->meals = SHRT_MAX;
	if (pthread_mutex_init(&monitor->death_mtx, NULL) != 0)
		return (printf("Monitor mutex init failed\n"), NULL);
	monitor->end = false;
	return (monitor);
}

static t_philo *philos_init(t_fork *fork, t_monitor *monitor)
{
	t_philo	*philos;
	int		i;

	philos = safe_malloc(monitor->n * sizeof(t_philo), "Error allocating philos");
	i = -1;
	while (++i < monitor->n)
	{
		philos[i].right_fork = fork;
		philos[i].left_fork = fork->next;
		philos[i].id = i + 1;
		philos[i].last_meal_time = 0;
		philos[i].meals_eaten = 0;
		philos[i].monitor = monitor;
		philos[i].full = false;
		fork = fork->next;
	}
	return (philos);
}

void	init_data(t_philo **philo, t_fork **fork,
		t_monitor **monitor, char **argv, struct timeval time)
{
	*fork = forks_init(argv[0]);
	*monitor = monitor_init(argv, time);
	*philo = philos_init(*fork, *monitor);
}
