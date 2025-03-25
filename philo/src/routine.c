/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/25 11:48:23 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*monitor_routine(t_philo *philo, t_monitor *mon)
{
	int			i;
	int			total_meals;
	int			meal_time;

	i = 0;
	total_meals = 0;
	while (!bool_getter(&mon->end, &mon->death_mtx))
	{
		total_meals += meal_counter(&philo[i], mon, &meal_time);
		if (timer(mon->sit_time) - meal_time >= mon->time_to_die)
		{
			custom_print(&philo[i], "died");
			bool_setter(&mon->end, true, &mon->death_mtx);
		}
		else if ((mon->n % 2 == 0 && total_meals > mon->n * mon->meals)
			|| (mon->n % 2 != 0 && total_meals > mon->n * mon->meals + 1))
			bool_setter(&mon->end, true, &mon->death_mtx);
		if (++i == mon->n)
		{
			i = 0;
			total_meals = 0;
		}
	}
	return (NULL);
}

static bool	eating(t_philo *philo)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	pthread_mutex_lock(&monitor->meals_mtx);
	philo->last_meal_time = timer(monitor->sit_time);
	philo->meals_eaten++;
	pthread_mutex_unlock(&monitor->meals_mtx);
	if (!custom_print(philo, "is eating"))
		return ((void)(forks_down(philo)), false);
	if (!uwait(philo->monitor->time_to_eat, &philo->monitor))
		return ((void)(forks_down(philo)), false);
	forks_down(philo);
	return (true);
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
	{
		custom_print(philo, "is thinking");
		uwait(philo->monitor->time_to_sleep / 2, &philo->monitor);
	}
	while (1)
	{
		if (!forks_pickup(philo))
			return (forks_down(philo));
		if (!eating(philo) || !custom_print(philo, "is sleeping")
			|| !uwait(philo->monitor->time_to_sleep, &philo->monitor))
			break ;
		if (!custom_print(philo, "is thinking") || !uwait(2, &philo->monitor))
			break ;
	}
	return (NULL);
}

void	dinner(t_philo *philo, t_monitor **monitor)
{
	int				i;
	struct timeval	time;

	i = -1;
	gettimeofday(&time, NULL);
	(*monitor)->sit_time = time;
	while (++i < (*monitor)->n)
		pthread_create(&philo[i].thread, NULL, philo_routine, &philo[i]);
	monitor_routine(philo, *monitor);
}
