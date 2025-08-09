/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 19:31:59 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks the validity of program arguments.
 * 
 * @param arr Array of argument strings.
 * @param len Number of arguments.
 * 
 * @return 0 if valid, -1 otherwise.
 */
static int	param_check(char **arr, int len)
{
	int	i;

	if (len != 4 && len != 5)
		return (-1);
	i = -1;
	while (++i < len)
	{
		if (is_valid_integer(arr[i]) == -1)
			return (-1);
		if (ft_atoi(arr[i]) < 0)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_fork			*fork;
	t_monitor		*monitor;

	if (param_check(++argv, --argc) == 0)
	{
		init_data(&philo, &fork, &monitor, argv);
		dinner(&philo, &monitor);
		join_n_free(&philo, &monitor, &fork);
	}
	return (0);
}
