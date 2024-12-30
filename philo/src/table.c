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
t_philo	*new_philo(int n)
{
	t_philo		*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->thread_id = n;
	philo->philo_id = n;
	philo->fork_up = false;
	philo->ate = false;
	philo->slept = false;
	philo->thought = false;
	philo->next_philo = NULL;
	return (philo);
}

/**
 * @brief Initializes the table with num number of philosophers.
 */
void	table_init(t_philo **head, int num)
{
	t_philo	*current;
	int		i;

	i = 1;
	(*head) = new_philo(i++);
	current = *head;
	while (i <= num)
	{
		current->next_philo = new_philo(i++);
		if (!current->next_philo)
			exit (1);
		current = current->next_philo;
	}
	current->next_philo = (*head);
}
