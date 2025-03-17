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
/**
 * @brief Timer should be a field on the monitor, and the thread should track
 * time with a custom nad more accurate usleep function.
 */
static void	*monitor_routine(t_philo *philo)
{
	int	i;
	t_monitor	*mon;

	i = 0;
	mon = philo[i].monitor;
	while (!end_getter(mon))
	{
		mon = philo[i].monitor;
		if (timer(philo[i].sit) - philo[i].last_meal_time >= mon->time_to_die
			|| philo[i].meals_eaten >= mon->meals)
			{
				printf("id: [%d], time: %ld, last meal: %ld\n", philo[i].id, timer(philo[i].sit), philo[i].last_meal_time);
				end_setter(mon);
			}
		if (++i == mon->n)
			i = 1;
	}
	return (NULL);
}

static void	*eating(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->right_fork->mtx);
	printf("%ld %d has taken a fork (%d)\n", timer(philo->sit), philo->id, philo->right_fork->id);
	pthread_mutex_lock(&philo->left_fork->mtx);
	printf("%ld %d is eating\n", timer(philo->sit), philo->id);
	while (1)
	{
		if (timer(philo->sit) - philo->last_meal_time >= philo->monitor->time_to_eat)
		{

			philo->last_meal_time = timer(philo->sit);
			philo->meals_eaten++;
			break ;
		}
		if (end_getter(philo->monitor))
		{
			break;
		}
		usleep(1000);
	}
	pthread_mutex_unlock(&philo->right_fork->mtx);
	pthread_mutex_unlock(&philo->left_fork->mtx);
	return (NULL);
}

/**
 * @brief The odd-number-id-philos are init with sleeping for half
 * their sleeping time.
 */
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// pause();
	if (philo->id % 2 != 0)
	{
		usleep(philo->monitor->time_to_sleep / 2);
		printf("%ld %d is sleeping initially\n", timer(philo->sit), philo->id);	
	}
	while (1)
	{
		eating(philo);
		if (philo->monitor->end)
			break;
		printf("%ld %d is sleeping\n", timer(philo->sit), philo->id);
	}
	// sleeping(philo);
	// thinking(philo);
	return (NULL);
}

void dinner(t_philo **philo, t_monitor **monitor)
{
	int		i;

	i = -1;
	while (++i < (*monitor)->n)
	{
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
	}
	monitor_routine(*philo);
	// pause();
}