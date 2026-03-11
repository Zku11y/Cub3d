/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_check_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:15:29 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/11 02:33:07 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ts_cln_pngs(t_nc *nu)
{
	int	i;

	i = WA;
	while (i <= HP && nu->txtrs[i])
	{
		mlx_delete_texture(nu->txtrs[i]);
		i++;
	}
}

int	ts_check_data(t_nc *nu)
{
	int	i;

	i = WA;
	if (!nu)
		return (1);
	if (!nu->imgs[WA] || !nu->imgs[FL] || !nu->imgs[ED]
		|| !nu->imgs[CI] || !nu->imgs[PR] || !nu->imgs[EN] || !nu->imgs[HP])
		return (1);
	while (i <= HP)
	{
		nu->txtrs[i] = mlx_load_png(nu->imgs[i]);
		if (!nu->txtrs[i])
			return (ts_cln_pngs(nu), 1);
		i++;
	}
	return (0);
}

t_elv	*get_elv(char **map, char who)
{
	t_elv	*hi;

	if (chk_elv(map))
		return (NULL);
	hi = ts_calloc(1, sizeof(t_elv));
	if (!hi)
		return (NULL);
	hi->y = 0;
	while (map[hi->y])
	{
		hi->x = 0;
		while (map[hi->y][hi->x])
		{
			if (map[hi->y][hi->x] == who)
			{
				hi->who = who;
				if (get_door(map, hi))
					return (free(hi), NULL);
				return (hi);
			}
			hi->x++;
		}
		hi->y++;
	}
	return (free(hi), NULL);
}

int	ts_floor(char c)
{
	return (c == '0' || c == 'D' || c == 'S' || c == 'E');
}

int	ts_edg_chk(char **map, int m_x, int m_y)
{
	int	x;
	int	y;

	y = 0;
	if (!map || m_x <= 0 || m_y <= 0)
		return (1);
	while (y < m_y)
	{
		x = 0;
		while (x < m_x)
		{
			if (ts_floor(map[y][x]))
			{
				if (x == 0 || y == 0 || x == m_x - 1 || y == m_y - 1)
					return (1);
				if (map[y + 1][x] == ' ' || map[y - 1][x] == ' '
					|| map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
