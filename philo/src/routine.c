/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/22 18:00:55 by dchrysov         ###   ########.fr       */
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
			custom_print(&philo[i], "died");
			end_setter(mon);
		}
		if (++i == mon->n)
			i = 1;
	}
	return (NULL);
}

/**
 * @returns false if simulation is over, true otherwise
 */
static bool	forks_pickup(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (end_getter(philo->monitor))
			return (false);
		custom_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (end_getter(philo->monitor))
			return (false);
		custom_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (end_getter(philo->monitor))
			return (false);
		custom_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (end_getter(philo->monitor))
			return (false);
		custom_print(philo, "has taken a fork");
	}
	philo->left_fork->fork_up = true;
	philo->right_fork->fork_up = true;
	return (true);
}

static bool	eating(t_philo *philo)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	if (end_getter(philo->monitor))
		return (false);
	custom_print(philo, "is eating");
	pthread_mutex_lock(&monitor->meals_mtx);
	philo->last_meal_time = timer(monitor->sit_time);
	if (philo->meals_eaten++ >= philo->monitor->meals)
		philo->full = true;
	pthread_mutex_unlock(&monitor->meals_mtx);
	activity(philo->monitor->time_to_eat, philo->monitor);
	pthread_mutex_unlock(&philo->right_fork->mtx);
	pthread_mutex_unlock(&philo->left_fork->mtx);
	philo->right_fork->fork_up = false;
	philo->left_fork->fork_up = false;
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
		activity(philo->monitor->time_to_sleep / 2, philo->monitor);
	}
	while (!philo->full)
	{
		if (!forks_pickup(philo) || !eating(philo)
			|| end_getter(philo->monitor))
			break ;
		custom_print(philo, "is sleeping");
		activity(philo->monitor->time_to_sleep, philo->monitor);
		if (end_getter(philo->monitor))
			break ;
		custom_print(philo, "is thinking");
	}
	return (NULL);
}

void	dinner(t_philo **philo, t_monitor **monitor)
{
	int				i;
	struct timeval	time;

	gettimeofday(&time, NULL);
	(*monitor)->sit_time = time;
	i = -1;
	while (++i < (*monitor)->n)
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
	monitor_routine(*philo);
}
