/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:45:54 by mdakni            #+#    #+#             */
/*   Updated: 2024/11/07 16:05:24 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

static size_t	ft_size(char const *s1, char const *set, size_t start)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i && ft_strchr(set, s1[i]) != NULL)
		i--;
	return (i - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_start(s1, set);
	if (ft_strlen(s1) == start)
		return (ft_strdup(""));
	len = ft_size(s1, set, start);
	return (ft_substr(s1, start, len));
}
