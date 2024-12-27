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

