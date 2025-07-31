/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:29:24 by mdakni            #+#    #+#             */
/*   Updated: 2024/11/07 09:30:38 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	size_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static void	free_mem(char **answer, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(answer[i++]);
	free(answer);
}

static char	**insert_word(char **answer, size_t count, char const *s, char c)
{
	size_t	i;
	size_t	index;

	i = 0;
	index = 0;
	while (index < count)
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			return (answer);
		answer[index] = ft_substr(s, i, size_word(s + i, c));
		if (answer[index] == NULL)
		{
			free_mem(answer, index);
			return (NULL);
		}
		i += size_word(s + i, c);
		index++;
	}
	return (answer);
}

char	**ft_split(char const *s, char c)
{
	char	**answer;
	int		i;
	size_t	count;

	if (!s)
		return (NULL);
	i = 0;
	count = count_word(s, c);
	answer = malloc(sizeof(char *) * (count + 1));
	if (answer == NULL)
		return (NULL);
	answer[count] = NULL;
	return (insert_word(answer, count, s, c));
}
