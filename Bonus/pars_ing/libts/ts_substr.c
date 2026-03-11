/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 05:23:21 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*ts_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ts_strlen(s))
	{
		str = ts_calloc(sizeof(char), 1);
		if (!str)
			return (NULL);
		ts_strlcpy(str, s, 1);
		return (str);
	}
	else
	{
		if (len < ts_strlen(&s[start]))
			n = len;
		else
			n = ts_strlen(&s[start]);
	}
	str = ts_calloc(sizeof(char), n + 1);
	if (!str)
		return (NULL);
	ts_strlcpy(str, s + start, n + 1);
	return (str);
}
