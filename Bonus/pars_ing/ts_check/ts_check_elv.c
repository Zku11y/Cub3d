/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_check_elv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:23:14 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:32:23 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ts_check_door(char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || !map[y + 1])
		return (1);
	if (map[y][x + 1] == '1' && map[y][x - 1] == '1')
	{
		if (map[y + 1][x] == '1' || map[y - 1][x] == '1')
			return (1);
		return (0);
	}
	else if (map[y + 1][x] == '1' && map[y - 1][x] == '1')
	{
		if (map[y][x + 1] == '1' || map[y][x - 1] == '1')
			return (1);
		return (0);
	}
	return (1);
}

int	ts_check_elvs_exist(char **map)
{
	int (x), (y), (i), (j), (k);
	y = 0;
	i = 0;
	j = 0;
	k = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' && i < 3)
				i++;
			if (map[y][x] == 'E' && j < 3)
				j++;
			if (map[y][x] == 'D' && k < 3)
				k++;
			x++;
		}
		y++;
	}
	if (i != 1 || j != 1 || k != 2)
		return (1);
	return (0);
}

int	ts_check_nb_door(char **map, int x, int y)
{
	if (map[y][x + 1] == 'D')
	{
		if (ts_check_door(map, x + 1, y))
			return (1);
	}
	else if (map[y][x - 1] == 'D')
	{
		if (ts_check_door(map, x - 1, y))
			return (1);
	}
	else if (map[y + 1][x] == 'D')
	{
		if (ts_check_door(map, x, y + 1))
			return (1);
	}
	else if (map[y - 1][x] == 'D')
	{
		if (ts_check_door(map, x, y - 1))
			return (1);
	}
	return (0);
}

int	ts_check_in_elv(char **map, int x, int y)
{
	if (x <= 0 || y <= 0 || !map[y + 1])
		return (1);
	if (map[y][x + 1] != 'D' && map[y][x + 1] != '1')
		return (1);
	if (map[y][x - 1] != 'D' && map[y][x - 1] != '1')
		return (1);
	if (map[y + 1][x] != 'D' && map[y + 1][x] != '1')
		return (1);
	if (map[y - 1][x] != 'D' && map[y - 1][x] != '1')
		return (1);
	if (ts_check_nb_door(map, x, y))
		return (1);
	return (0);
}

int	ts_check_elv(char **map)
{
	int	x;
	int	y;

	y = 0;
	if (!map)
		return (1);
	if (ts_check_elvs_exist(map))
		return (1);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'E')
			{
				if (ts_check_in_elv(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
