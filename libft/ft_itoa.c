/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:34:35 by mdakni            #+#    #+#             */
/*   Updated: 2024/11/05 20:48:18 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*int_min_handler(void)
{
	int		i;
	char	*ptr;
	char	*str;

	i = 0;
	str = "-2147483648";
	ptr = malloc(12);
	if (ptr == NULL)
		return (NULL);
	while (i <= 11)
	{
		ptr[i] = str[i];
		i++;
	}
	return (ptr);
}

static int	size_of_int(int n)
{
	int	size;

	size = 1;
	if (n < 0)
	{
		n = -n;
		size++;
	}
	while (n > 9)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*converter(int n, char *ptr, int i)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		n = -n;
		sign = -1;
	}
	while (i > 0)
	{
		i--;
		if (sign == -1 && i == 0)
		{
			ptr[i] = '-';
			break ;
		}
		ptr[i] = (n % 10) + '0';
		n = n / 10;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ptr;
	int		sign;

	if (n == -2147483648)
		return (int_min_handler());
	sign = 1;
	i = size_of_int(n);
	ptr = malloc(i + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[i] = '\0';
	return (converter(n, ptr, i));
}
