/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:05:42 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/26 16:43:43 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	custom_print(t_philo *philo, char *msg)
{
	t_monitor	*mon;

	mon = philo->monitor;
	pthread_mutex_lock(&mon->print_mtx);
	printf("%ld %d %s\n", timer(mon->sit_time), philo->id, msg);
	pthread_mutex_unlock(&mon->print_mtx);
	return (true);
}

bool	uwait(long milliseconds, t_monitor **monitor)
{
	struct timeval	start;
	long			elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (!bool_getter(&(*monitor)->end, &(*monitor)->death_mtx))
	{
		elapsed = timer(start);
		if (elapsed > milliseconds)
			return (true);
		usleep(100);
	}
	return (false);
}

/**
 * @brief Updates the values of meal time and 
 */
int	meal_counter(t_philo *philo, t_monitor *mon, unsigned int *meal_time)
{
	int	count;

	pthread_mutex_lock(&mon->meals_mtx);
	*meal_time = philo->last_meal_time;
	count = philo->meals_eaten;
	pthread_mutex_unlock(&mon->meals_mtx);
	return (count);
}

static void	free_circular_list(t_fork **head, int n)
{
	t_fork	*temp;
	t_fork	*next_node;
	int		i;

	if (!head || !*head || n <= 0)
		return ;
	temp = *head;
	i = -1;
	while (++i < n - 1)
		temp = temp->next;
	temp->next = NULL;
	temp = *head;
	i = -1;
	while (++i < n)
	{
		next_node = temp->next;
		pthread_mutex_destroy(&temp->mtx);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

void	join_n_free(t_philo **philo, t_monitor **monitor, t_fork **fork_node)
{
	unsigned int	i;

	i = -1;
	while (++i < (*monitor)->n)
		pthread_join((*philo)[i].thread, NULL);
	free_circular_list(fork_node, (*monitor)->n);
	pthread_mutex_destroy(&(*monitor)->death_mtx);
	pthread_mutex_destroy(&(*monitor)->print_mtx);
	pthread_mutex_destroy(&(*monitor)->meals_mtx);
	free(*monitor);
	*monitor = NULL;
}
