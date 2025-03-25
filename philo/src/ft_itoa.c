/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:09:39 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/25 17:00:43 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static unsigned long	ft_strlen(const char *str)
{
	unsigned long	len;

	if (!str)
		return (0);
	len = 0;
	while (*str++)
		len++;
	return (len);
}

static char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;
	int		i;

	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = -1;
	while (s[++i])
		ptr[i] = s[i];
	ptr[i] = '\0';
	return (ptr);
}

static int	ft_divisor(int num)
{
	int	i;
	int	div;

	i = 1;
	div = 1;
	if (num < 0)
		num *= -1;
	while (i <= (num / 10))
	{
		i *= 10;
		div *= 10;
	}
	return (div);
}

static int	ft_count_dig(int num)
{
	int	count;

	count = 0;
	if (num <= 0)
		count ++;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

static char	*ft_inttochar(char *ptr, int n, int d)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		ptr[i++] = '-';
		n *= -1;
	}
	while (d > 0)
	{
		ptr[i++] = (n / d) + '0';
		n %= d;
		d /= 10;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		div;

	if (n == INT_MIN)
		result = ft_strdup("-2147483648");
	else
	{
		result = (char *)malloc(ft_count_dig(n) * sizeof(char) + 1);
		if (result == NULL)
			return (NULL);
		else
		{
			div = ft_divisor(n);
			result = ft_inttochar(result, n, div);
		}
	}
	return (result);
}
