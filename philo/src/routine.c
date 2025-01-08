/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/27 14:02:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	eating(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->fork);
	pthread_mutex_lock(&(*philo)->next_philo->fork);
	printf("%s%ld %d has taken a fork\n", YEL, duration_since((*philo)->start), (*philo)->philo_id);
	printf("%ld %d is eating\n", duration_since((*philo)->start), (*philo)->philo_id);
	(*philo)->last_meal = duration_since((*philo)->start);
	usleep((ft_atoi((*philo)->params[1]) - duration_since((*philo)->start)) * 1000);
	pthread_mutex_unlock(&(*philo)->fork);
	pthread_mutex_unlock(&(*philo)->next_philo->fork);
}

static void	sleeping(t_philo *philo)
{
	printf("%s%ld %d is sleeping\n", PUR, duration_since(philo->start), philo->philo_id);
	usleep((ft_atoi(philo->params[2]) - duration_since(philo->start)) * 1000);
}

static void	thinking(t_philo *philo)
{
	printf("%s%ld %d is thinking\n", BL, duration_since(philo->start), philo->philo_id);
	usleep((ft_atoi(philo->params[0]) - ft_atoi(philo->params[1]) - ft_atoi(philo->params[2])) * 1000);
}

/**
 * @brief routine function for thread creating.
 */
void *routine(void *args)
{
	t_philo			*philo;

	philo = (t_philo *)args;
	while (1)
	{
		eating(&philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
