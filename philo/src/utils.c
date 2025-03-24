/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/24 19:27:32 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @returns False if simulation is over, true otherwise
 * 
 * @note Makes even-id philos to pickup the right fork first, the other way
 * around for the left-id ones.
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
		if (!philo->left_fork)
			return (false);
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

/**
 * @brief Set down a philo's forks, with the opposite order of how they got
 * picked up.
 */
void	*forks_down(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->mtx);
		bool_setter(&philo->left_fork->fork_up, false,
			&philo->left_fork->mtx);
		pthread_mutex_unlock(&philo->right_fork->mtx);
		bool_setter(&philo->right_fork->fork_up, false,
			&philo->right_fork->mtx);
	}
	else
	{
		if (philo->right_fork)
		{
			pthread_mutex_unlock(&philo->right_fork->mtx);
			bool_setter(&philo->right_fork->fork_up, false,
				&philo->right_fork->mtx);
		}
		if (philo->left_fork)
		{
			pthread_mutex_unlock(&philo->left_fork->mtx);
			bool_setter(&philo->left_fork->fork_up, false,
				&philo->left_fork->mtx);
		}
	}
	return (NULL);
}

/**
 * @brief Updates the values of meal time and 
 */
int	meal_counter(t_philo *philo, t_monitor *mon, int *meal_time)
{
	int	count;

	count = 0;
	pthread_mutex_lock(&mon->meals_mtx);
	*meal_time = philo->last_meal_time;
	count += philo->meals_eaten;
	pthread_mutex_unlock(&mon->meals_mtx);
	return (count);
}
