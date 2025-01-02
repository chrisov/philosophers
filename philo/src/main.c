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
		printf("%s(Error): Invalid arguments!\n%s", RED, RES);
		exit (0);
	}
	is_valid_integer(arr);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;

	param_check(++argv, --argc);
	table_init(&philo, argv);

	pthread_create(&philo->thread_id, NULL, routine, philo);
	pthread_create(&philo->next_philo->thread_id, NULL, routine, philo);
	pthread_join(philo->thread_id, NULL);
	pthread_join(philo->next_philo->thread_id, NULL);
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->next_philo->fork);
	return (0);
}
