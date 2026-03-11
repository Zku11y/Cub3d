/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 03:07:09 by oel-mado          #+#    #+#             */
/*   Updated: 2026/02/27 17:05:29 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*ts_strndup(const char *s1, size_t n)
{
	size_t	ln;
	char	*s2;

	ln = ts_strlen(s1);
	if (ln > n)
		ln = n;
	s2 = malloc(sizeof(char) * (ln + 1));
	if (!s2)
		return (NULL);
	ts_strlcpy(s2, s1, ln + 1);
	return (s2);
}
