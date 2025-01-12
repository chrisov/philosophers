/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:10 by dchrysov          #+#    #+#             */
/*   Updated: 2025/01/08 12:34:45 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief Creates a new philosopher
 */
static t_philo	*new_philo(int id, char **params, struct timeval start_time)
{
	t_philo			*philo;
	pthread_mutex_t	fork_mtx;
	pthread_mutex_t	meal_mtx;

	pthread_mutex_init(&fork_mtx, NULL);
	pthread_mutex_init(&meal_mtx, NULL);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (0);
	philo->id = id;
	philo->fork = fork_mtx;
	philo->last_meal_mtx = meal_mtx;
	philo->time_to_die = ft_atoi(params[1]);
	philo->time_to_eat = ft_atoi(params[2]);
	philo->time_to_sleep = ft_atoi(params[3]);
	if (params[4])
		philo->meals = ft_atoi(params[4]);
	else
		philo->meals = INT_MAX;
	philo->sit = start_time;
	philo->last_meal = 0;
	philo->finish = false;
	philo->next_philo = NULL;
	return (philo);
}

/**
 * @brief Initializes the table with philosophers.
 * 
 * @param params Stores the duration that each philo needs to eat, sleep, think.
 */
void	table_init(t_philo **head, t_table *table, char **params, struct timeval start)
{
	t_philo	*current;
	int		i;

	table->n = ft_atoi(params[0]);
	table->finished_meals = 0;
	table->philo = NULL;
	i = 1;
	(*head) = new_philo(i++, params, start);
	if (!head)
		exit (0);
	current = *head;
	while (i <= table->n)
	{
		current->next_philo = new_philo(i++, params, start);
		if (!current->next_philo)
			exit (0);
		current = current->next_philo;
	}
	current->next_philo = (*head);
	table->philo = *head;
}
