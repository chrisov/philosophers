/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/25 17:01:58 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	monitor_routine(t_philo *philo, t_monitor *mon)
{
	int			i;
	int			total_meals;
	int			last_meal;

	i = 0;
	total_meals = 0;
	while (1)
	{
		total_meals += meal_counter(&philo[i], mon, &last_meal);
		if (timer(mon->sit_time) - last_meal >= mon->time_to_die)
			return ((void)(custom_print(&philo[i], "died")),
				bool_setter(&mon->end, true, &mon->death_mtx));
		else if ((mon->n % 2 == 0 && total_meals > mon->n * mon->meals)
			|| (mon->n % 2 != 0 && total_meals > mon->n * mon->meals + 1))
			return (bool_setter(&mon->end, true, &mon->death_mtx));
		if (++i == mon->n)
		{
			i = 0;
			total_meals = 0;
		}
	}
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
		bool_setter(&philo->r_fork->up, false, &philo->r_fork->mtx);
		(*fork_count)--;
		bool_setter(&philo->l_fork->up, false, &philo->l_fork->mtx);
		(*fork_count)--;
		return (true);
	}
	return (forks_down(philo, fork_count), false);
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
	if (philo->id % 2 != 0)
	{
		custom_print(philo, "is thinking");
		uwait(philo->monitor->time_to_sleep / 2, &philo->monitor);
	}
	count_f = 0;
	while (1)
	{
		count_f += forks_pickup(philo);
		if (!count_f)
			break ;
		custom_print(philo, "1 fork");
		if (count_f == 2)
		{
			if (!eating(philo, &count_f) || !custom_print(philo, "is sleeping")
				|| !uwait(philo->monitor->time_to_sleep, &philo->monitor))
				break ;
			if (!custom_print(philo, "is thinking"))
				break ;
			uwait(7, &philo->monitor);
			custom_print(philo, ft_itoa(count_f));
		}
	}
	return (NULL);
}

void	dinner(t_philo **philo, t_monitor **monitor)
{
	int				i;
	struct timeval	time;

	i = -1;
	gettimeofday(&time, NULL);
	(*monitor)->sit_time = time;
	while (++i < (*monitor)->n)
		pthread_create(&(*philo)[i].thread, NULL, philo_routine, &(*philo)[i]);
	monitor_routine(*philo, *monitor);
}
