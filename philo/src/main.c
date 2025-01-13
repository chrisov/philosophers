/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/13 13:14:49 by dchrysov         ###   ########.fr       */
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
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)args;
	philo = table->philo;
	while (!philo->finish)
	{
		pthread_mutex_lock(&philo->last_meal_mtx);
		if (timer(philo->sit) - philo->last_meal > philo->time_to_die)
		{
			printf("%ld %d died\n", timer(philo->sit), philo->id);
			pthread_mutex_unlock(&philo->last_meal_mtx);
			exit (0);
		}
		pthread_mutex_unlock(&philo->last_meal_mtx);
		philo = philo->next_philo;
	}
	if (philo->finish)
		table->finished_meals++;
	return (NULL);
}

/**
 * @brief Thread creation and synchronization.
 */
static void	dinner(t_philo *philo, t_table table)
{
	int			i;

	i = 0;
	while (i++ < table.n)
	{
		pthread_create(&philo->thread_id, NULL, routine, philo);
		philo = philo->next_philo;
	}
	pthread_create(&table.monitor, NULL, monitor_table, &table);
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_table			table;
	struct timeval	time;

	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	table_init(&philo, &table, argv, time);
	dinner(philo, table);
	safe_free(philo, table);
	return (0);
}
