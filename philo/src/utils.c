/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 14:47:36 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

static void	single_fork_down(t_fork *fork, int *count)
{
	if (bool_getter(&fork->up, &fork->mtx))
	{
		bool_setter(&fork->up, false, &fork->mtx);
		(*count)--;
	}
}

/**
 * @brief Makes even-id philos to pickup the right fork first, the other way
 * around for the left-id ones.
 * 
 * @returns The number of picked up forks, -3 in case of a philo's death
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
 * @returns False if simulation is over, true otherwise
 * 
 * @brief Makes even-id philos to pickup the right fork first, the other way
 * around for the left-id ones.
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
 * @brief Makes odd number of philos to think at the beginning of the sim
 */
void	philo_init(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		custom_print(philo, "is thinking");
		uwait(philo->monitor->time_to_sleep / 2, &philo->monitor);
	}
}
