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
	char			**times;

	times = params;
	pthread_mutex_init(&fork_mtx, NULL);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->philo_id = id;
	philo->fork = fork_mtx;
	philo->params = ++times;
	philo->start = start_time;
	philo->last_meal = 0;
	philo->next_philo = NULL;
	return (philo);
}

/**
 * @brief Initializes the table with philosophers.
 * 
 * @param params Stores the times that each philo needs to eat, sleep and think.
 */
void	table_init(t_philo **head, char **params, struct timeval start)
{
	t_philo	*current;
	int		i;

	i = 1;
	(*head) = new_philo(i++, params, start);
	current = *head;
	while (i <= ft_atoi(params[0]))
	{
		current->next_philo = new_philo(i++, params, start);
		if (!current->next_philo)
			exit (1);
		current = current->next_philo;
	}
	current->next_philo = (*head);
}
