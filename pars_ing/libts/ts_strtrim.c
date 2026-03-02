/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:28:39 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*ts_strtrim(char const *s1, char const *set)
{
	size_t	f;
	size_t	l;

	f = 0;
	if (!s1 || !set)
		return (NULL);
	if (s1 == NULL)
		return (ts_calloc(sizeof(char), 1));
	l = ts_strlen(s1);
	if (set == NULL || !l)
		return (ts_strdup(s1));
	l--;
	while (s1[f] && ts_strchr(set, s1[f]))
		f++;
	while (l > f && ts_strrchr(set, s1[l]))
		l--;
	return (ts_substr(s1, f, l - f + 1));
}
