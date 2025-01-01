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

static void	monitor_table(t_philo *philo, long start)
{
	struct timeval	now;
	t_philo			*current;
	unsigned int	starting_id;

	starting_id = philo->philo_id;
	current = philo->next_philo;
	while (1)
	{
		gettimeofday(&now, NULL);
		if (current->fork_up || current->next_philo->fork_up
			|| now.tv_usec - current->last_meal > ft_atoi(current->actvt_time[0]))
		{
			printf("[%ld] %d died\n", now.tv_usec - start, philo->philo_id);
			// free()
			exit(0);
		}
		if (current->philo_id == starting_id)
			break ;
		current = current->next_philo;
	}
}

static void	eating(t_philo *philo, long start)
{
	struct timeval	now;

	monitor_table(philo, start);
	pthread_mutex_lock(&philo->fork);
	philo->fork_up = true;
	pthread_mutex_lock(&philo->next_philo->fork);
	philo->next_philo->fork_up = true;
	gettimeofday(&now, NULL);
	printf("[%ld] %d has taken a fork", now.tv_usec - start, philo->philo_id);
	printf("[%ld] %d is eating", now.tv_usec - start, philo->philo_id);
	while (1)
	{
		gettimeofday(&now, NULL);
		if (now.tv_usec - start >= ft_atoi(philo->actvt_time[1]))
		{
			philo->last_meal = now.tv_usec - start;
			pthread_mutex_unlock(&philo->fork);
			philo->fork_up = false;
			pthread_mutex_unlock(&philo->next_philo->fork);
			philo->next_philo->fork_up = false;
			break ;
		}
	}
}

static void	thinking(t_philo *philo, long start)
{
	struct timeval	now;

	monitor_table(philo, start);
	gettimeofday(&now, NULL);
	printf("[%ld] %d is thinking", now.tv_usec - start, philo->philo_id);
}

static void	sleeping(t_philo *philo, long start)
{
	struct timeval	now;

	monitor_table(philo, start);
	gettimeofday(&now, NULL);
	printf("[%ld] %d is sleeping", now.tv_usec - start, philo->philo_id);
}

static void *routine(void *args)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *)args;
	gettimeofday(&start, NULL);
	eating(philo, start.tv_usec);
	gettimeofday(&start, NULL);
	thinking(philo, start.tv_usec);
	gettimeofday(&start, NULL);
	sleeping(philo, start.tv_usec);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		times;

	param_check(++argv, --argc);
	table_init(&philo, argv);
	if (argv[4])
	{
		times = ft_atoi(argv[4]);
		while (times-- != 0)
		{
			pthread_create(&philo->thread_id, NULL, routine, &philo);
			philo = philo->next_philo;
		}
	}
	times = ft_atoi(argv[4]);
	while (times-- != 0)
	{
		pthread_join(philo->thread_id, NULL);
		pthread_mutex_destroy(&philo->fork);
		philo = philo->next_philo;
	}
	// else

	// while (philo)
	// {
	// }
	// int j = 0;
	// while (j++ < 20)
	// {
	// 	printf("%d ", philo->philo_id);
	// 	printf("[");
	// 	int k = 0;
	// 	while (k < 4)
	// 		printf("%s ", philo->actvt_time[k++]);
	// 	printf("] -> \n");
	// 	philo = philo->next_philo;
	// }
	return (0);
}
