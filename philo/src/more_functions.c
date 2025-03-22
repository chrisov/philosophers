/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:05:42 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/22 17:43:38 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	custom_print(t_philo *philo, char *msg)
{
	t_monitor	*mon;

	mon = philo->monitor;
	pthread_mutex_lock(&mon->print_mtx);
	printf("%ld %d %s\n", timer(mon->sit_time), philo->id, msg);
	pthread_mutex_unlock(&mon->print_mtx);
}

void	activity(long milliseconds, t_monitor *monitor)
{
	struct timeval	start;
	long			elapsed;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (!end_getter(monitor) && elapsed < milliseconds)
	{
		elapsed = timer(start);
		if (milliseconds - elapsed > 100)
			usleep(100);
	}
}
