/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/23 15:53:05 by dchrysov         ###   ########.fr       */
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
	t_fork	*fork_head;
	t_fork	*current;
	int		i;

	i = 1;
	fork_head = safe_malloc(sizeof(t_fork), "Error allocating fork");
	fork_head->fork_up = false;
	if (pthread_mutex_init(&fork_head->mtx, NULL) != 0)
		return (printf("Mutex init failed\n"), NULL);
	current = fork_head;
	while (++i < ft_atoi(param) + 1)
	{
		current->next = safe_malloc(sizeof(t_fork), "Error allocating fork");
		current = current->next;
		current->fork_up = false;
		if (pthread_mutex_init(&current->mtx, NULL) != 0)
			return (printf("Fork mutex init failed\n"), NULL);
		current->next = NULL;
	}
	current->next = fork_head;
	return (fork_head);
}

/**
 * @brief Init monitor with program's params and the philo list.
 */
static t_monitor	*monitor_init(char **param)
{
	t_monitor	*monitor;

	monitor = safe_malloc(sizeof(t_monitor), "Error allocating monitor");
	monitor->n = ft_atoi(param[0]);
	monitor->time_to_die = ft_atoi(param[1]);
	monitor->time_to_eat = ft_atoi(param[2]);
	monitor->time_to_sleep = ft_atoi(param[3]);
	if (param[4])
		monitor->meals = ft_atoi(param[4]);
	else
		monitor->meals = SHRT_MAX;
	if (pthread_mutex_init(&monitor->death_mtx, NULL) != 0)
		return (printf("Death mutex init failed\n"), NULL);
	if (pthread_mutex_init(&monitor->print_mtx, NULL) != 0)
		return (printf("Print mutex init failed\n"), NULL);
	if (pthread_mutex_init(&monitor->meals_mtx, NULL) != 0)
		return (printf("Meals mutex init failed\n"), NULL);
	monitor->end = false;
	return (monitor);
}

static t_philo	*philos_init(t_fork *fork, t_monitor *monitor)
{
	t_philo	*philos;
	int		i;

	philos = safe_malloc(monitor->n * sizeof(t_philo),
			"Error allocating philos");
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

void	init_data(t_philo **philo, t_fork **fork, t_monitor **mon, char **argv)
{
	*fork = forks_init(argv[0]);
	*mon = monitor_init(argv);
	*philo = philos_init(*fork, *mon);
}
