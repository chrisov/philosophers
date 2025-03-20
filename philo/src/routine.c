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
 * @brief 
 */
static void	*monitor_routine(t_philo *philo)
{
	int			i;
	t_monitor	*mon;

	i = 0;
	mon = philo[i].monitor;
	while (!end_getter(mon))
	{
		mon = philo[i].monitor;
		if (timer(mon->sit_time) - philo[i].last_meal_time >= mon->time_to_die)
		{
			printf("%ld %d died\n", timer(mon->sit_time), philo[i].id);
			end_setter(mon);
		}
		else if (philo[i].meals_eaten >= mon->meals)
			end_setter(mon);
		if (++i == mon->n)
			i = 1;
	}
	return (NULL);
}

static void	*eating(t_philo *philo)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&philo->right_fork->mtx);
	printf("%ld %d has taken a fork\n", timer(monitor->sit_time), philo->id);
	pthread_mutex_lock(&philo->left_fork->mtx);
	printf("%ld %d is eating\n", timer(philo->monitor->sit_time), philo->id);
	philo->last_meal_time = timer(monitor->sit_time);
	activity(philo->monitor->time_to_eat, philo->monitor);
	philo->last_meal_time = timer(monitor->sit_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->right_fork->mtx);
	pthread_mutex_unlock(&philo->left_fork->mtx);
	return (NULL);
}

static void	thinking(t_philo *philo)
{
	t_monitor	*mon;

	mon = philo->monitor;
	printf("%ld %d is thinking\n", timer(mon->sit_time), philo->id);
	activity(mon->time_to_die - mon->time_to_eat - mon->time_to_sleep, mon);
}

/**
 * @brief The odd-number-id-philos are init with sleeping for half
 * their sleeping time.
 */
static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		activity(philo->monitor->time_to_sleep / 2, philo->monitor);
	while (1)
	{
		if (end_getter(philo->monitor))
			break;
		eating(philo);
		if (end_getter(philo->monitor))
			break;
		printf("%ld %d is sleeping\n", timer(philo->monitor->sit_time), philo->id);
		activity(philo->monitor->time_to_sleep, philo->monitor);
		if (end_getter(philo->monitor))
			break;
		thinking(philo);
	}
	return (NULL);
}

void dinner(t_philo **philo, t_monitor **monitor)
{
	int		i;

	i = -1;
	while (++i < (*monitor)->n)
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
	monitor_routine(*philo);
	// pause();
}