/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 03:07:09 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

char	*ts_strdup(const char *s1)
{
	size_t	ln;
	char	*s2;

	ln = ts_strlen(s1) + 1;
	s2 = malloc(sizeof(char) * ln);
	if (!s2)
		return (NULL);
	ts_strlcpy(s2, s1, ln);
	return (s2);
}
