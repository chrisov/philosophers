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
		err_msg("Error! (Invalid argument)");
	is_valid_integer(arr);
}

int	main(int argc, char **argv)
{
	struct timeval	time;
	t_philo			*philo;

	philo = NULL;
	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	init(&philo, argv, time);
	dinner(&philo);
	safe_free(philo);
	return (0);
}
