/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 14:25:12 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	is_valid_integer(char *str)
{
	if (*str == '\0')
	{
		printf("%sError! (invalid argument)%s\n", RED, RES);
		exit(EXIT_FAILURE);
	}
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
		{
			printf("%sError! (invalid argument)%s\n", RED, RES);
			exit(EXIT_FAILURE);
		}
		str++;
	}
}

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

void	bool_setter(bool *var, bool value, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

bool	bool_getter(bool *var, pthread_mutex_t *mutex)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *var;
	pthread_mutex_unlock(mutex);
	return (res);
}

/**
 * @brief Calculates time passed since the beginning of the program run.
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
