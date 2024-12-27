/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/27 14:02:37 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	param_check(char **arr, int len)
{
	if (len != 4 && len != 5)
	{
		printf("%sWrong number of parameters!\n%s", RED, RES);
		exit (0);
	}
	is_valid_integer(arr);
}

static void	create_philo(int n, t_philo *philo)
{
	int	i;

	i = 1;
	while (i <= n)
	{
		philo->index = i++;
		philo->fork = false;
		philo->ate = false;
		philo->slept = false;
		philo->thought = false;
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	fork;
	t_philo			philo;

	param_check(++argv, --argc);
	pthread_mutex_init(&fork, NULL);

	return (0);
}
