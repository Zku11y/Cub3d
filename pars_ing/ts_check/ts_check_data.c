/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_check_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:15:29 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/09 17:23:48 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ts_cln_pngs(t_nc *nu)
{
	int	i;

	i = WA;
	while (i <= ED && nu->txtrs[i])
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
		|| !nu->imgs[CI] || !nu->imgs[PR] || !nu->imgs[EN])
		return (1);
	while (i <= ED)
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
