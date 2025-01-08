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

// static void	monitor_table(t_philo *philo)
// {
// 	t_philo			*current;
// 	unsigned int	starting_id;
// 	struct timeval	start;

// 	starting_id = philo->philo_id;
// 	current = philo->next_philo;
// 	while (1)
// 	{
// 		gettimeofday(&start, NULL);
// 		if (duration_since(start) - current->last_meal > ft_atoi(current->param[0]))
// 		{
// 			printf("[%ld] %d died\n", duration_since(start), current->philo_id);
// 			// free()
// 			exit(0);
// 		}
// 		if (current->philo_id == starting_id)
// 			break ;
// 		current = current->next_philo;
// 		usleep(1000);
// 	}
// }

int	main(int argc, char **argv)
{
	t_philo			*philo;
	// pthread_t		monitor;
	struct timeval	time;
	int				i;

	param_check(++argv, --argc);
	gettimeofday(&time, NULL);
	table_init(&philo, argv, time);
	i = 0;
	// pthread_create(&monitor, NULL, monitor_table, philo);
	while (i++ < ft_atoi(argv[0]))
	{
		pthread_create(&philo->thread_id, NULL, routine, philo);
		philo = philo->next_philo;
	}
	// pthread_create(&philo->next_philo->thread_id, NULL, routine, philo->next_philo);
	// pthread_create(&philo->next_philo->next_philo->thread_id, NULL, routine, philo->next_philo->next_philo);
	// pthread_join(monitor, NULL);
	pthread_join(philo->thread_id, NULL);
	// pthread_join(philo->next_philo->thread_id, NULL);
	// pthread_join(philo->next_philo->next_philo->thread_id, NULL);
	// pthread_mutex_destroy(&monitor);
	pthread_mutex_destroy(&philo->fork);
	// pthread_mutex_destroy(&philo->next_philo->fork);
	// pthread_mutex_destroy(&philo->next_philo->next_philo->fork);
	return (0);
}
