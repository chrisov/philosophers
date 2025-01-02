/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:28:51 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/27 13:50:25 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
			if (!ft_isdigit((unsigned char)*str))
			{
				printf("%sError! (invalid argument)%s\n", RED, RES);
				exit(0);
			}
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
	while (*str && ft_isdigit(*str))
	{
			res = res * 10 + (*str - '0');
			str++;
	}
	return (sign * res);
}

long	duration(struct timeval start)
{
	struct timeval	now;
	long			sec;
	long			usec;

	gettimeofday(&now, NULL);
	sec = now.tv_sec - start.tv_sec;
	usec = now.tv_usec - start.tv_usec;
	return ((sec + usec / 1e6) * 1e3);
}
