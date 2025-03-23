/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:22:59 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/23 18:03:17 by dchrysov         ###   ########.fr       */
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


