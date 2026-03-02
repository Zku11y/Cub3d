/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 00:03:26 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*ts_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	ptr = ts_calloc(sizeof(char), (ts_strlen(s) + 1));
	if (!ptr)
		return (ptr);
	if (!s)
	{
		ptr = NULL;
		return (ptr);
	}
	while (i < ts_strlen(s))
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	return (ptr);
}
