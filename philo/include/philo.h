/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:09:21 by dchrysov          #+#    #+#             */
/*   Updated: 2024/12/27 15:19:13 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define RED "\033[1;31m"
# define YEL "\033[33m"
# define BL "\033[34m"
# define PUR "\033[35m"
# define RES "\033[0m"

typedef struct s_philo
{
	unsigned int	philo_id;
	pthread_t		thread_id;
	pthread_mutex_t	fork;
	struct timeval	start;
	long			last_meal;
	char			**params;
	struct s_philo	*next_philo;
}			t_philo;

void	is_valid_integer(char **arr);
int		ft_atoi(const char *str);
long	duration_since(struct timeval start);
void	table_init(t_philo **head, char **params, struct timeval start);
void	*routine(void *args);

#endif