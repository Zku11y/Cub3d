/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cln.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:22:47 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/09 20:36:43 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	map_cln(char **map, int x, int y, t_elv *hi)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '8' || map[i][j] == ' ')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	put_door(char **map, t_elv *hi)
{
	printf("IN::x%d,y%d\n", hi->x, hi->y);
	write(1, "WTF\n", 4);
	if (hi->door == 'N')
	{
		hi->d_x = hi->x;
		hi->d_y = hi->y - 1;
		// map[hi->y][hi->x - 1] = 'D';
	}
	if (hi->door == 'S')
	{
		hi->d_x = hi->x;
		hi->d_y = hi->y + 1;
		// map[hi->y][hi->x + 1] = 'D';
	}
	if (hi->door == 'E')
	{
		hi->d_x = hi->x + 1;
		hi->d_y = hi->y;
		// map[hi->y + 1][hi->x] = 'D';
	}
	if (hi->door == 'W')
	{
		hi->d_x = hi->x - 1;
		hi->d_y = hi->y;
		// map[hi->y - 1][hi->x] = 'D';
	}
}

int	rec_path(char **map, int x, int y, int *m_s)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > m_s[1])
		return (0);
	if (y > m_s[0])
		return (0);
	if (map[y][x] == '9' || map[y][x] == '1'
		|| map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'P')
		return (0);
	if (map[y][x] == '0')
		map[y][x] = '9';
	if (map[y][x] == 'D')
		map[y][x] = 'P';
	rec_path(map, x + 1, y, m_s);
	rec_path(map, x, y + 1, m_s);
	rec_path(map, x - 1, y, m_s);
	rec_path(map, x, y - 1, m_s);
	return (0);
}

int	cln_path(char **map, int *m_s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < m_s[1] && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '9')
				map[i][j] = '0';
			if (map[i][j] == 'P')
			{
				map[i][j] = 'D';
				k++;
			}
			j++;
		}
		i++;
	}
	return (k);
}

int	get_path(char **map, t_elv *elv, int *m_s)
{
	int	ret;

	ret = 1;
	if (elv->door == 'N')
		ret = rec_path(map, elv->x, elv->y - 1, m_s);
	if (elv->door == 'S')
		ret = rec_path(map, elv->x, elv->y + 1, m_s);
	if (elv->door == 'E')
		ret = rec_path(map, elv->x + 1, elv->y, m_s);
	if (elv->door == 'W')
		ret = rec_path(map, elv->x - 1, elv->y, m_s);
	if (cln_path(map, m_s) != 2)
		return (1);
	return (ret);
}
