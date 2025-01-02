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

/**
 * @brief Creates a new philosopher
 */
static t_philo	*new_philo(int id, char **params)
{
	t_philo			*philo;
	pthread_mutex_t	fork_mtx;
	char			**times;

	times = params;
	pthread_mutex_init(&fork_mtx, NULL);
	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->thread_id = id;
	philo->philo_id = id;
	philo->fork = fork_mtx;
	philo->actvt_time = ++times;
	philo->fork_up = false;
	philo->last_meal = 0;
	philo->next_philo = NULL;
	return (philo);
}

/**
 * @brief Initializes the table with philosophers.
 * 
 * @param params Stores the times that each philo needs to eat, sleep and think.
 */
void	table_init(t_philo **head, char **params)
{
	t_philo	*current;
	int		i;

	i = 1;
	(*head) = new_philo(i++, params);
	current = *head;
	while (i <= ft_atoi(params[0]))
	{
		current->next_philo = new_philo(i++, params);
		if (!current->next_philo)
			exit (1);
		current = current->next_philo;
	}
	current->next_philo = (*head);
}
