/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/25 16:44:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @returns False if simulation is over, true otherwise
 * 
 * @note Makes even-id philos to pickup the right fork first, the other way
 * around for the left-id ones.
 */
int	forks_pickup(t_philo *philo)
{
	int	res;

	res = 0;
	if (philo->id % 2 == 0)
	{
		if (!bool_getter(&philo->r_fork->up, &philo->r_fork->mtx))
		{
			bool_setter(&philo->r_fork->up, true, &philo->r_fork->mtx);
			if (!custom_print(philo, "has taken a fork"))
				return (0);
			res++;
		}
		if (!bool_getter(&philo->l_fork->up, &philo->l_fork->mtx))
		{
			bool_setter(&philo->l_fork->up, true, &philo->l_fork->mtx);
			if (!custom_print(philo, "has taken a fork"))
				return (0);
			res++;
		}
	}
	else
	{
		if (philo->l_fork && !bool_getter(&philo->l_fork->up, &philo->l_fork->mtx))
		{
			bool_setter(&philo->l_fork->up, true, &philo->l_fork->mtx);
			if (!custom_print(philo, "has taken a fork"))
				return (0);
			res++;
		}
		if (!bool_getter(&philo->r_fork->up, &philo->r_fork->mtx))
		{
			bool_setter(&philo->r_fork->up, true, &philo->r_fork->mtx);
			if (!custom_print(philo, "has taken a fork"))
				return (0);
			res++;
		}
	}
	return (res);
}

/**
 * @brief Set down a philo's forks, with the opposite order of how they got
 * picked up.
 */
void	*forks_down(t_philo *philo, int *fork_count)
{
	if (philo->id % 2 == 0)
	{
		if (bool_getter(&philo->r_fork->up, &philo->r_fork->mtx))
		{
			bool_setter(&philo->r_fork->up, false, &philo->r_fork->mtx);
			(*fork_count)--;
		}
		if (bool_getter(&philo->l_fork->up, &philo->l_fork->mtx))
		{
			bool_setter(&philo->l_fork->up, false, &philo->l_fork->mtx);
			(*fork_count)--;
		}
	}
	else
	{
		if (philo->l_fork
			&& !bool_getter(&philo->l_fork->up, &philo->l_fork->mtx))
		{
			bool_setter(&philo->l_fork->up, true, &philo->l_fork->mtx);
			(*fork_count)--;
		}
		if (!bool_getter(&philo->r_fork->up, &philo->r_fork->mtx))
		{
			bool_setter(&philo->r_fork->up, true, &philo->r_fork->mtx);
			(*fork_count)--;
		}
	}
	return (NULL);
}
