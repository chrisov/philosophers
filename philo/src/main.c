/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/24 18:54:28 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Checks the program's arguments for invalidity.
 */
static void	param_check(char **arr, int len)
{
	int	i;

	if (len != 4 && len != 5)
	{
		printf("%sError!%s (Invalid argument)\n", RED, RES);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < len)
	{
		is_valid_integer(arr[i]);
		if (ft_atoi(arr[i]) < 0)
		{
			printf("%sOut of range argument...%s\n", RED, RES);
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_fork			*fork;
	t_monitor		*monitor;

	param_check(++argv, --argc);
	init_data(&philo, &fork, &monitor, argv);
	dinner(&philo, &monitor);
	join_n_free(&philo, &monitor, &fork);
	return (0);
}
