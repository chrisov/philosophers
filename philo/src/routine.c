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

static void	monitor_table(t_philo *philo, struct timeval start)
{
	t_philo			*current;
	unsigned int	starting_id;

	starting_id = philo->philo_id;
	current = philo->next_philo;
	while (1)
	{
		if (current->fork_up || current->next_philo->fork_up
			|| duration(start) - current->last_meal > ft_atoi(current->actvt_time[0]))
		{
			printf("[%d] %d died\n", duration(start), current->philo_id);
			// free()
			exit(0);
		}
		if (current->philo_id == starting_id)
			break ;
		current = current->next_philo;
		usleep(1000);
	}
}

static void	eating(t_philo **philo, long *time)
{
	struct timeval	start;

	// monitor_table(*philo, start);
	gettimeofday(&start, NULL);
	pthread_mutex_lock(&(*philo)->fork);
	(*philo)->fork_up = true;
	pthread_mutex_lock(&(*philo)->next_philo->fork);
	(*philo)->next_philo->fork_up = true;
	*time += duration(start);
	printf("%s[%ld] %d has taken a fork\n", YEL, *time, (*philo)->philo_id);
	printf("[%ld] %d is eating\n", *time, (*philo)->philo_id);
	while (1)
	{
		if (duration(start) >= ft_atoi((*philo)->actvt_time[1]))
		{
			// (*philo)->last_meal = now.tv_usec - start;
			pthread_mutex_unlock(&(*philo)->fork);
			(*philo)->fork_up = false;
			pthread_mutex_unlock(&(*philo)->next_philo->fork);
			(*philo)->next_philo->fork_up = false;
			break ;
		}
		usleep(1000);
	}
}

static long	thinking(t_philo *philo, long *time)
{
	struct timeval	start;

	// monitor_table(philo, start);
	gettimeofday(&start, NULL);
	while (1)
	{
		if (duration(start) >= ft_atoi(philo->actvt_time[2]))
		{
			*time += ft_atoi(philo->actvt_time[2]);
			printf("%s[%ld] %d is thinking\n", BL, *time, philo->philo_id);
			break ;
		}
		usleep(1000);
	}
	return (ft_atoi(philo->actvt_time[2]));
}

static void	sleeping(t_philo *philo, long *time)
{
	struct timeval	start;

	// monitor_table(philo, start);
	gettimeofday(&start, NULL);
	while (1)
	{
		if (duration(start) >= ft_atoi(philo->actvt_time[1]))
		{
			*time += ft_atoi(philo->actvt_time[1]);
			printf("%s[%ld] %d is sleeping\n", PUR, *time, philo->philo_id);
			break ;
		}
		usleep(1000);
	}
}

void *routine(void *args)
{
	t_philo			*philo;
	long			elapsed_time;

	philo = (t_philo *)args;
	elapsed_time = 0;
	while (1)
	{
		eating(&philo, &elapsed_time);
		sleeping(philo, &elapsed_time);
		thinking(philo, &elapsed_time);
	}
	return (NULL);
}