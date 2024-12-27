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
# define RES "\033[0m"

typedef struct s_philo
{
	pthread_t		id;
	unsigned int	index;
	bool			fork;
	bool			ate;
	bool			slept;
	bool			thought;
}			t_philo;

void	is_valid_integer(char **arr);

#endif