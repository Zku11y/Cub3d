/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:55:02 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

void	*ts_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = dst;
	s = src;
	if (!dst && !src)
		return (dst);
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
