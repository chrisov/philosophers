/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 13:14:27 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	is_valid_integer(char **arr)
{
	char	**current;
	char	*str;

	current = arr;
	while (*current)
	{
		str = *current;
		if (*str == '+' || *str == '-')
			str++;
		if (*str == '\0')
			exit(0);
		while (*str)
		{
			if (!(*str >= '0' && *str <= '9'))
				err_msg("Error! (invalid argument)");
			str++;
		}
		current++;
	}
}

int	ft_atoi(const char *str)
{
	int	res;
	int	count;
	int	sign;

	res = 0;
	count = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		if (count > 0)
			return (0);
		str++;
		count++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
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
	return ((sec + usec / 1e6) * 1e3);
}

/**
 * @brief Prints a custom msg every time it encounters an error.
 */
void	err_msg(char *msg)
{
        printf("%s%s%s\n",RED, msg, RES);
        exit(EXIT_FAILURE);
}

/**
 * @brief Safe freeing everything.
 */
// void	safe_free(t_philo *philo)
// {
// 	int	i;
// 	int	n;

// 	i = -1;
// 	n = philo->table->n;
// 	// join threads
// 	while (++i < n)
// 	{
// 		pthread_mutex_destroy(&philo[i].fork->mtx);
// 		free(philo[i].fork);
// 	}
// 	free(philo->table);
// 	free(philo);
// 	philo = NULL;
// }
