/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 15:38:47 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks the program's arguments for invalidity.
 */
static void	param_check(char **arr, int len)
{
	if (len != 4 && len != 5)
	{
		printf("%s(Error)! Invalid argument!\n%s", RED, RES);
		exit (0);
	}
	is_valid_integer(arr);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_philo			*philo;
	t_fork			*fork;


	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	philo = NULL;
	init(&philo, &fork, argv, time);	

	return (0);
}
