/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:13:08 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:31:58 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rec(char **map, int x, int y, int *m_s)
{
	if (x < 0 || y < 0 || x >= m_s[0] || y >= m_s[1])
		return (1);
	if (map[x][y] == ' ' || map[x][y] == '\0')
		return (1);
	if (map[x][y] == '8' || map[x][y] == '1' || map[x][y] == 'D')
		return (0);
	if (map[x][y] == '0')
		map[x][y] = '8';
	else
		return (0);
	if (rec(map, x + 1, y, m_s) == 1)
		return (1);
	if (rec(map, x, y + 1, m_s) == 1)
		return (1);
	if (rec(map, x - 1, y, m_s) == 1)
		return (1);
	if (rec(map, x, y - 1, m_s) == 1)
		return (1);
	return (0);
}

int	chk_elv(char **map)
{
	int (i), (j), (s);
	i = 0;
	s = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				s++;
			else if (map[i][j] != '0' && map[i][j] != '1'
				&& map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != ' ' && !(map[i][j] >= 9
				&& map[i][j] <= 13))
				return (1);
			if (s > 3)
				return (1);
			j++;
		}
		i++;
	}
	if (s == 0)
		return (1);
	return (0);
}

int	get_door(char **map, t_elv *hi)
{
	if (map[hi->y][hi->x - 1] == 'D')
	{
		hi->door = 'W';
		return (ts_check_door(map, hi->x - 1, hi->y));
	}
	if (map[hi->y][hi->x + 1] == 'D')
	{
		hi->door = 'E';
		return (ts_check_door(map, hi->x + 1, hi->y));
	}
	if (map[hi->y + 1][hi->x] == 'D')
	{
		hi->door = 'S';
		return (ts_check_door(map, hi->x, hi->y + 1));
	}
	if (map[hi->y - 1][hi->x] == 'D')
	{
		hi->door = 'N';
		return (ts_check_door(map, hi->x, hi->y - 1));
	}
	return (1);
}

int	*go_rec(char **map, int x, int y, t_elv *start)
{
	int		*m_s;
	int		ret;

	m_s = ts_calloc(2, sizeof(int));
	if (!m_s)
		return (NULL);
	m_s[0] = 0;
	while (map[m_s[0]])
		m_s[0]++;
	m_s[1] = ts_strlen(map[0]);
	if (m_s[0] < 3 || m_s[1] < 3)
		return (NULL);
	if (start->door == 'N')
		ret = rec(map, x, y + 2, m_s);
	if (start->door == 'S')
		ret = rec(map, x, y - 2, m_s);
	if (start->door == 'E')
		ret = rec(map, x + 2, y, m_s);
	if (start->door == 'W')
		ret = rec(map, x - 2, y, m_s);
	if (ret)
		return (NULL);
	return (m_s);
}

int	rec_map(char **map, t_nc *nu)
{
	int		*m_s;

	if (ts_check_elv(map))
		return (1);
	nu->start = get_elv(map, 'S');
	if (!nu->start)
		return (1);
	nu->end = get_elv(map, 'E');
	if (!nu->end)
		return (free(nu->start), 1);
	m_s = go_rec(map, nu->start->y, nu->start->x, nu->start);
	if (!m_s)
		return (free(nu->start), free(nu->end), 1);
	map_cln(map, nu->start->y, nu->start->x, nu->start);
	if (get_path(map, nu->start, m_s))
		return (free(m_s), free(nu->start), free(nu->end), 1);
	free(m_s);
	return (0);
}
