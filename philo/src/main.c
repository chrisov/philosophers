/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/22 12:58:52 by dchrysov         ###   ########.fr       */
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
		printf("%sError!%s (Invalid argument)\n", RED, RES);
		exit(EXIT_FAILURE);
	}
	is_valid_integer(arr);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_fork			*fork;
	t_monitor		*monitor;

	param_check(++argv, --argc);
	init_data(&philo, &fork, &monitor, argv);
	dinner(&philo, &monitor);
	// safe_free(philo);
	return (0);
}
