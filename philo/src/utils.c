/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/24 17:01:27 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @returns false if simulation is over, true otherwise
 */
bool	forks_pickup(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		bool_setter(&philo->right_fork->fork_up, true, &philo->right_fork->mtx);
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (!custom_print(philo, "has taken a fork"))
			return (false);
		bool_setter(&philo->left_fork->fork_up, true, &philo->left_fork->mtx);
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (!custom_print(philo, "has taken a fork"))
			return (false);
	}
	else
	{
		bool_setter(&philo->left_fork->fork_up, true, &philo->left_fork->mtx);
		pthread_mutex_lock(&philo->left_fork->mtx);
		if (!custom_print(philo, "has taken a fork"))
			return (false);
		bool_setter(&philo->right_fork->fork_up, true, &philo->right_fork->mtx);
		pthread_mutex_lock(&philo->right_fork->mtx);
		if (!custom_print(philo, "has taken a fork"))
			return (false);
	}
	return (true);
}

void	*forks_down(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (bool_getter(&philo->left_fork->fork_up, &philo->left_fork->mtx))
		{
			pthread_mutex_unlock(&philo->left_fork->mtx);
			bool_setter(&philo->left_fork->fork_up, false,
				&philo->left_fork->mtx);
		}
		if (bool_getter(&philo->right_fork->fork_up, &philo->right_fork->mtx))
		{
			pthread_mutex_unlock(&philo->right_fork->mtx);
			bool_setter(&philo->right_fork->fork_up, false,
				&philo->right_fork->mtx);
		}
	}
	else
	{
		if (bool_getter(&philo->right_fork->fork_up, &philo->right_fork->mtx))
		{
			pthread_mutex_unlock(&philo->right_fork->mtx);
			bool_setter(&philo->right_fork->fork_up, false,
				&philo->right_fork->mtx);
		}
		if (bool_getter(&philo->left_fork->fork_up, &philo->left_fork->mtx))
		{
			pthread_mutex_unlock(&philo->left_fork->mtx);
			bool_setter(&philo->left_fork->fork_up, false,
				&philo->left_fork->mtx);
		}
	}
	return (NULL);
}

int	meal_counter(t_philo *philo, t_monitor *mon, int *last_meal)
{
	int	count;

	pthread_mutex_lock(&mon->meals_mtx);
	*last_meal = philo->last_meal_time;
	count = philo->meals_eaten;
	pthread_mutex_unlock(&mon->meals_mtx);
	return (count);
}
