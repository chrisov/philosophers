/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 19:28:49 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks if a string represents a valid integer.
 * 
 * @param str The string to check.
 * 
 * @return 0 if valid, -1 otherwise.
 */
int	is_valid_integer(char *str)
{
	if (*str == '\0')
		return (-1);
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (-1);
		str++;
	}
	return (0);
}

/**
 * @brief Converts a string to an integer.
 * 
 * @param str The string to convert.
 * 
 * @return The integer value, or INT_MIN on overflow.
 */
int	ft_atoi(char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (INT_MIN);
		str++;
	}
	return ((int)(result * sign));
}

/**
 * @brief Sets a boolean variable in a thread-safe manner.
 * 
 * @param var Pointer to the boolean variable.
 * @param value Value to set.
 * @param mutex Mutex to lock during the operation.
 */
void	bool_setter(bool *var, bool value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

/**
 * @brief Gets the value of a boolean variable in a thread-safe manner.
 * 
 * @param var Pointer to the boolean variable.
 * @param mutex Mutex to lock during the operation.
 * 
 * @return The value of the variable.
 */
bool	bool_getter(bool *var, pthread_mutex_t *mutex)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

/**
 * @brief Calculates the elapsed time in milliseconds since a given start time.
 * 
 * @param start The start time.
 * 
 * @return Elapsed time in milliseconds.
 */
long	timer(struct timeval start)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - start.tv_sec;
	usec = now.tv_usec - start.tv_usec;
	return (sec * 1000 + usec / 1000);
}
