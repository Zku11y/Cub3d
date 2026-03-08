/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:41 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:12:42 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_map_init(t_cube *cube, t_nc *nu)
{
	int	i;

	i = 0;
	cube->map = ts_calloc(nu->y + 1, sizeof(char *));
	cube->floor_map = ts_calloc(nu->y + 1, sizeof(char *));
	if (cube->map == NULL)
		(mlx_terminate(cube->mlx)), (perror("Alloc error : ")),
			(exit(EXIT_FAILURE));
	if (cube->floor_map == NULL)
		(mlx_terminate(cube->mlx)), (perror("Alloc error : ")),
			(exit(EXIT_FAILURE));
	while (i < nu->y)
	{
		cube->map[i] = ts_calloc(nu->x + 1, sizeof(char));
		if (cube->map[i] == NULL)
			(mlx_terminate(cube->mlx)), (perror("Alloc error : ")),
				(exit(EXIT_FAILURE));
		i++;
	}
	cube->map = nu->map;
}
