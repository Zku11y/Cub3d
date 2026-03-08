/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:09:54 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 00:19:11 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ts_rgb_check(char *val)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (val[i] && j < 3 && (val[i] == ','
			|| (val[i] >= '0' && val[i] <= '9')))
	{
		if (val[i] == ',')
			j++;
		i++;
	}
	if (j != 2 || val[i])
		return (1);
	return (0);
}

int	ts_byte(char *val, int *ret)
{
	long	c;
	int		i;

	i = 0;
	while (val[i] && val[i] != ',')
		i++;
	if (!i)
		return (0);
	c = ts_atoi(val);
	if (c < 0 || c > 255)
		return (0);
	*ret = c;
	return (i);
}

int	ts_rgb(char *val, int *r, int *g, int *b)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!val)
		return (1);
	if (ts_rgb_check(val))
		return (1);
	j = ts_byte(val, r);
	if (!j)
		return (1);
	i += j + 1;
	j = ts_byte(&val[i], g);
	if (!j)
		return (1);
	i += j + 1;
	j = ts_byte(&val[i], b);
	if (!j)
		return (1);
	return (0);
}
