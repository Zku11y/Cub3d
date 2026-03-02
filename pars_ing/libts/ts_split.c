/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:56:25 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

static char	**frre(char **arr, int i)
{
	while (--i >= 0)
		free (arr[i]);
	free (arr);
	return (NULL);
}

static int	f_words(const char *str, char c)
{
	int	i;
	int	j;
	int	word;

	i = 0;
	j = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] == c)
			j = 0;
		else if (j == 0)
		{
			j = 1;
			word++;
		}
		i++;
	}
	return (word);
}

static char	**m_lit(char **arr, int word, const char *str, char c)
{
	char	*next;

	int (i), (j), (k);
	i = 0;
	k = 0;
	while (word)
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			next = ts_strchr(&str[i], c);
			if (!next)
				j = ts_strlen(&str[i]);
			else
				j = next - &str[i];
			arr[k++] = ts_substr(&str[i], 0, j);
			if (!arr[k - 1])
				return (frre(arr, k));
			i = i + j;
		}
		word--;
	}
	return (arr);
}

char	**ts_split(const char *str, char c)
{
	int		word;
	char	**arr;

	if (!str)
		return (NULL);
	word = f_words(str, c);
	arr = ts_calloc(sizeof(char *), word + 1);
	if (!arr)
		return (NULL);
	return (m_lit(arr, word, str, c));
}
