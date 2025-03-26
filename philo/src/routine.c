/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 14:48:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	*monitor_routine(t_philo *philo, t_monitor *mon)
{
	unsigned int	i;
	unsigned int	total_meals;
	unsigned int	last_meal;

	i = 0;
	total_meals = 0;
	while (1)
	{
		total_meals += meal_counter(&philo[i], mon, &last_meal);
		if (timer(mon->sit_time) - last_meal >= mon->time_to_die)
			return (bool_setter(&mon->end, true, &mon->death_mtx), &philo[i]);
		else if ((mon->n % 2 == 0 && total_meals > mon->n * mon->meals)
			|| (mon->n % 2 != 0 && total_meals > mon->n * mon->meals + 1))
			return (bool_setter(&mon->end, true, &mon->death_mtx), NULL);
		if (++i == mon->n)
		{
			usleep(100);
			i = 0;
			total_meals = 0;
		}
	}
}

static bool	sleeping(t_philo *philo)
{
	if (!custom_print(philo, "is sleeping"))
		return (false);
	uwait(philo->monitor->time_to_sleep, &philo->monitor);
	return (true);
}

static bool	eating(t_philo *philo, int *fork_count)
{
	t_monitor	*monitor;

	monitor = philo->monitor;
	if (bool_getter(&monitor->end, &monitor->death_mtx))
		return (forks_down(philo, fork_count), false);
	if (bool_getter(&philo->r_fork->up, &philo->r_fork->mtx)
		&& bool_getter(&philo->l_fork->up, &philo->l_fork->mtx))
	{
		pthread_mutex_lock(&monitor->meals_mtx);
		philo->last_meal_time = timer(monitor->sit_time);
		philo->meals_eaten++;
		pthread_mutex_unlock(&monitor->meals_mtx);
		if (!custom_print(philo, "is eating"))
			return (forks_down(philo, fork_count), false);
		uwait(philo->monitor->time_to_eat, &philo->monitor);
		return (forks_down(philo, fork_count), true);
	}
	return (false);
}

/**
 * @brief The odd-number-id-philos are init with sleeping for half
 * their sleeping time.
 */
static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		count_f;

	philo = (t_philo *)arg;
	philo_init(philo);
	count_f = 0;
	while (1)
	{
		count_f += forks_pickup(philo);
		if (count_f < 0)
			return (forks_down(philo, &count_f), NULL);
		if (count_f == 2)
		{
			if (!eating(philo, &count_f))
				return (forks_down(philo, &count_f), NULL);
			if (!sleeping(philo))
				return (forks_down(philo, &count_f), NULL);
			custom_print(philo, "is thinking");
			if (bool_getter(&philo->monitor->end, &philo->monitor->death_mtx))
				return (forks_down(philo, &count_f), NULL);
			usleep(100);
		}
	}
	return (NULL);
}

void	dinner(t_philo **philo, t_monitor **monitor)
{
	unsigned int	i;
	struct timeval	time;
	t_philo			*dead;

	i = -1;
	gettimeofday(&time, NULL);
	(*monitor)->sit_time = time;
	while (++i < (*monitor)->n)
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
	dead = monitor_routine(*philo, *monitor);
	usleep(3200);
	if (dead)
		printf("%s%ld %d died%s\n", RED,
			timer((*monitor)->sit_time), dead->id, RES);
}
