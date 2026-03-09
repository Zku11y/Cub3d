/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:41 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 21:28:54 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_map_init(t_cube *cube, t_nc *nu)
{
	int	i;

	i = 0;
	cube->map = ts_calloc(nu->y + 1, sizeof(char *));
	if (cube->map == NULL)
		return (ft_clean(cube, cube->nu, 1));
	while (i < nu->y)
	{
		cube->map[i] = ts_calloc(nu->x + 1, sizeof(char));
		if (cube->map[i] == NULL)
			return (ft_clean(cube, cube->nu, 1));
		i++;
	}
	cube->map = nu->map;
}
