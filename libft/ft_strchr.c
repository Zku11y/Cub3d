/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 23:23:53 by mdakni            #+#    #+#             */
/*   Updated: 2024/11/05 11:20:09 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t		i;
	const char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		ptr = &s[i];
	return ((char *)ptr);
}
