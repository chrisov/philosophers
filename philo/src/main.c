/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/08 14:40:14 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	param_check(char **arr, int len)
{
	if (len != 4 && len != 5)
	{
		printf("%s(Error): Invalid arguments!\n%s", RED, RES);
		exit (0);
	}
	is_valid_integer(arr);
	if (ft_atoi(arr[0]) == 1)
	{
		printf("Not enough forks\n");
		exit (0);
	}
}

static void	*monitor_table(void *args)
{
	t_philo			*philo;
	t_philo			*current;
	unsigned int	starting_id;

	philo = (t_philo *)args;
	starting_id = philo->philo_id;
	current = philo->next_philo;
	while (1)
	{
		if (stopwatch(current->start) - current->last_meal > current->time_to_die)
		{
			printf("%ld %d died\n", stopwatch(current->start), current->philo_id);
			// free()
			exit(0);
		}
		if (current->philo_id == starting_id)
			break ;
		current = current->next_philo;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	pthread_t		monitor;
	struct timeval	time;
	int				i;

	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	table_init(&philo, argv, time);
	i = 0;
	while (i++ < ft_atoi(argv[0]))
	{
		pthread_create(&philo->thread_id, NULL, routine, philo);
		pthread_create(&monitor, NULL, monitor_table, philo);
		pthread_join(monitor, NULL);
		philo = philo->next_philo;
	}
	i = 0;
	while (i++ < ft_atoi(argv[0]))
	{
		pthread_join(philo->thread_id, NULL);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next_philo;
	}
	safe_free(philo);
	return (0);
}
