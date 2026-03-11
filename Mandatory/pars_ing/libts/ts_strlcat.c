/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 02:56:44 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

size_t	ts_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (!dst && !n)
		return (ts_strlen(src));
	k = ts_strlen((const char *)dst);
	if (n < ts_strlen(dst))
		return (ts_strlen(src) + n);
	while (dst[i] && i + 1 < n)
		i++;
	while (src[j] && i + j + 1 < n)
	{
		dst[i + j] = src[j];
		j++;
		dst[i + j] = '\0';
	}
	return (k + ts_strlen(src));
}
