/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/08 13:39:21 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eating(t_philo **philo)
{
	long	func_start;

	pthread_mutex_lock(&(*philo)->fork);
	pthread_mutex_lock(&(*philo)->next_philo->fork);
	printf("%ld %d has taken a fork\n", stopwatch((*philo)->start), (*philo)->philo_id);
	printf("%ld %d is eating\n", stopwatch((*philo)->start), (*philo)->philo_id);
	func_start = stopwatch((*philo)->start);
	pthread_mutex_lock(&(*philo)->last_meal_mtx);
	(*philo)->last_meal = func_start;
	pthread_mutex_unlock(&(*philo)->last_meal_mtx);
	while (1)
	{
		if (stopwatch((*philo)->start) >= func_start + (*philo)->time_to_eat)
		{
			pthread_mutex_unlock(&(*philo)->fork);
			pthread_mutex_unlock(&(*philo)->next_philo->fork);
			break ;
		}
		usleep(1000);
	}
	(*philo)->meals--;
}

static void	sleeping(t_philo *philo)
{
	long	func_start;

	printf("%ld %d is sleeping\n", stopwatch(philo->start), philo->philo_id);
	func_start = stopwatch(philo->start);
	while (1)
	{
		if (stopwatch(philo->start) >= func_start + philo->time_to_sleep)
			break ;
	}
}

static void	thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", stopwatch(philo->start), philo->philo_id);
}

/**
 * @brief routine function for thread creating.
 */
void	*routine(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	while (1)
	{
		eating(&philo);
		sleeping(philo);
		thinking(philo);
		if (philo->meals == 0)
		{
			philo->finish = true;
			break ;
		}
	}
	return (NULL);
}
