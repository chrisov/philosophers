/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 13:44:23 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	eating(t_philo **philo)
{
	long	begin_eat;

	pthread_mutex_lock(&(*philo)->fork);
	if ((*philo)->next_philo != *philo)
	{
		pthread_mutex_lock(&(*philo)->next_philo->fork);
		printf("%ld %d has taken a fork\n", timer((*philo)->sit), (*philo)->id);
		printf("%ld %d is eating\n", timer((*philo)->sit), (*philo)->id);
		begin_eat = timer((*philo)->sit);
		pthread_mutex_lock(&(*philo)->last_meal_mtx);
		(*philo)->last_meal = begin_eat;
		pthread_mutex_unlock(&(*philo)->last_meal_mtx);
		while (1)
		{
			if (timer((*philo)->sit) >= begin_eat + (*philo)->time_to_eat)
			{
				pthread_mutex_unlock(&(*philo)->fork);
				pthread_mutex_unlock(&(*philo)->next_philo->fork);
				break ;
			}
		}
		(*philo)->meals--;
	}
}

static void	sleeping(t_philo *philo)
{
	long	begin_sleep;

	printf("%ld %d is sleeping\n", timer(philo->sit), philo->id);
	begin_sleep = timer(philo->sit);
	while (1)
	{
		if (timer(philo->sit) >= begin_sleep + philo->time_to_sleep)
			break ;
	}
}

/**
 * @brief Philosophers's routine function.
 */
void	*routine(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	while (!philo->finish)
	{
		eating(&philo);
		sleeping(philo);
		printf("%ld %d is thinking\n", timer(philo->sit), philo->id);
		if (philo->meals == 0)
			philo->finish = true;
	}
	return (NULL);
}
