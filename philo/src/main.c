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

/**
 * @brief Routine function for the monitoring thread.
 */
static void	*monitor_table(void *args)
{
	t_philo			*philo;
	t_philo			*current;

	philo = (t_philo *)args;
	current = philo->next_philo;
	while (!philo->finish)
	{
		pthread_mutex_lock(&philo->last_meal_mtx);
		if (timer(current->sit) - current->last_meal > current->time_to_die)
		{
			printf("%ld %d died\n", timer(current->sit), current->id);
			pthread_mutex_unlock(&philo->last_meal_mtx);
			exit(0);
		}
		pthread_mutex_unlock(&philo->last_meal_mtx);
		current = current->next_philo;
	}
	return (NULL);
}

/**
 * @brief Thread creation and synchronization.
 */
static void	dinner(t_philo *philo, int n)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	while (i++ < n)
	{
		pthread_create(&philo->thread_id, NULL, routine, philo);
		philo = philo->next_philo;
	}
	pthread_create(&monitor, NULL, monitor_table, philo);
	i = 0;
	while (i++ < n)
	{
		pthread_mutex_destroy(&philo->fork);
		pthread_mutex_destroy(&philo->last_meal_mtx);
		pthread_join(philo->thread_id, NULL);
		philo = philo->next_philo;
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	struct timeval	time;

	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	table_init(&philo, argv, time);
	dinner(philo, ft_atoi(argv[0]));
	// safe_free(philo);
	return (0);
}
