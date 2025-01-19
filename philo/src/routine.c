/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 15:38:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// static void	*monitor_routine(void *arg)
// {
// 	(void)arg;
// 	return (NULL);
// }

static void	*eating(void *arg)
{
	t_philo	*philo;
	t_fork	*right_fork;
	t_fork	*left_fork;

	philo = (t_philo *)arg;
	right_fork = &philo->table->fork[philo->id];
	left_fork = &philo->table->fork[(philo->id + 1) % philo->table->n];
	pthread_mutex_lock(&right_fork->mtx);
	printf("[%ld] %d: took fork %d\n", timer(philo->sit), philo->id, right_fork->fork_id);
	pthread_mutex_lock(&left_fork->mtx);
	printf("[%ld] %d: took fork %d\n", timer(philo->sit), philo->id, left_fork->fork_id);
	usleep(philo->table->time_to_eat * 1000);
	printf("%ld\n", timer(philo->sit));
	// pthread_mutex_unlock(&philo->fork->mtx);
	// pthread_mutex_unlock(&philo[(philo->id + 1) % philo->table->n].fork->mtx);
	return (NULL);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
		eating(philo);
	// sleeping(philo);
	// thinking(philo);
	return (NULL);
}

void dinner(t_philo **philo)
{
	int		i;
	t_table	*table;

	table = (*philo)->table;
	i = -1;
	while (++i < table->n)
		pthread_create(&(*philo)[i].thread_id, NULL, philo_routine, &(*philo)[i]);
	// pthread_create(table->monitor, NULL, monitor_routine, table);
}