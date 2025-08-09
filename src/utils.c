/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 16:20:24 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Picks up a single fork for a philosopher if available.
 * 
 * @param philo Pointer to the philosopher.
 * @param fork Pointer to the fork.
 * @param count Pointer to the fork count.
 * 
 * @return true if fork was picked up or not needed, false otherwise.
 */
static bool	single_fork_pickup(t_philo *philo, t_fork *fork, int *count)
{
	if (fork && !bool_getter(&fork->up, &fork->mtx))
	{
		bool_setter(&fork->up, true, &fork->mtx);
		if (!custom_print(philo, "has taken a fork"))
			return (false);
		(*count)++;
	}
	return (true);
}

/**
 * @brief Puts down a single fork for a philosopher.
 * 
 * @param fork Pointer to the fork.
 * @param count Pointer to the fork count.
 */
static void	single_fork_down(t_fork *fork, int *count)
{
	if (fork && bool_getter(&fork->up, &fork->mtx))
	{
		bool_setter(&fork->up, false, &fork->mtx);
		(*count)--;
	}
}

/**
 * @brief Handles fork pickup logic for a philosopher.
 * 
 * @param philo Pointer to the philosopher.
 * 
 * @return Number of forks picked up, or -3 if philosopher died.
 */
int	forks_pickup(t_philo *philo)
{
	int	res;

	res = 0;
	if (philo->id % 2 == 0)
	{
		if (!single_fork_pickup(philo, philo->r_fork, &res))
			return (-3);
		if (!single_fork_pickup(philo, philo->l_fork, &res))
			return (-3);
	}
	else
	{
		if (!single_fork_pickup(philo, philo->l_fork, &res))
			return (-3);
		if (!single_fork_pickup(philo, philo->r_fork, &res))
			return (-3);
	}
	return (res);
}

/**
 * @brief Handles fork put-down logic for a philosopher.
 * 
 * @param philo Pointer to the philosopher.
 * @param fork_count Pointer to the fork count.
 */
void	forks_down(t_philo *philo, int *fork_count)
{
	if (philo->id % 2 == 0)
	{
		single_fork_down(philo->l_fork, fork_count);
		single_fork_down(philo->r_fork, fork_count);
	}
	else
	{
		single_fork_down(philo->r_fork, fork_count);
		single_fork_down(philo->l_fork, fork_count);
	}
}

/**
 * @brief Initializes a philosopher's state at the start of the simulation.
 * 
 * @param philo Pointer to the philosopher.
 */
void	philo_init(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		custom_print(philo, "is thinking");
		uwait(philo->monitor->time_to_sleep / 2, &philo->monitor);
	}
}
