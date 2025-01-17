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

/**
 * @brief Prints a std msg every time it encounters an error.
 */
static void     err_msg(char *msg)
{
        printf("%s\n", msg);
        exit(0);
}

static void	create_forks(t_fork **fork, char **av)
{
	t_fork	*current;
	int		i;
	int		n;

	n = ft_atoi(av[0]);
	*fork = malloc(n * sizeof(t_fork));
	if (!fork)
		err_msg("Error allocating memory for the forks");
	current = *fork;
	i = 0;
	while (n--)
	{
		current->fork_id = i++;
		pthread_mutex_init(&current->mtx, NULL);
	}
}

static void	create_philos(t_philo **philo, char **av, struct timeval time)
{
	t_philo *current;
	int		n;
	int		i;

	n = ft_atoi(av[0]);
	*philo = malloc(n * sizeof(t_philo));
	if (!philo)
		err_msg("Error allocating memory for philos");
	current = *philo;
	i = 0;
	while (n--)
	{
		current->id = i++;
		current->sit = time;
		current->full = false;
		current++;
	}
}

static void	create_table(t_table **table, char **av)
{
	(*table)->n = ft_atoi(av[0]);
	(*table)->time_to_die = ft_atoi(av[1]);
	(*table)->time_to_eat = ft_atoi(av[2]);
	(*table)->time_to_sleep = ft_atoi(av[3]);
	if (av[4])
		(*table)->meals = ft_atoi(av[4]);
	else
		(*table)->meals = INT_MAX;
}

void	init(t_philo **philo, t_fork **fork, char **argv, struct timeval time)
{
	create_philos(philo, argv, time);
	create_forks(fork, argv);
	create_table(&(*philo)->table, argv);
}