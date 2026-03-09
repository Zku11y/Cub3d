/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:46 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 16:41:14 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_grid2(t_cube *cube, t_vars13 *vars)
{
	vars->y = vars->start_y;
	vars->x = vars->start_x;
	vars->i = -1;
	while (++vars->i < cube->mini_map_size)
	{
		vars->j = 0;
		while (vars->j < cube->mini_map_size)
		{
			vars->dst = sqrt(((double)vars->i - (cube->mini_map_size / 2.0))
					* ((double)vars->i - (cube->mini_map_size / 2.0))
					+ ((double)vars->j - (cube->mini_map_size / 2.0))
					* ((double)vars->j - (cube->mini_map_size / 2.0)));
			if (vars->dst < 0.08 * cube->screen_width_buff)
				mlx_put_pixel(cube->image, vars->i, vars->j, 0x010101ff);
			vars->j++;
		}
	}
}

void	draw_grid1(t_cube *cube, t_vars13 *vars)
{
	vars->start_y = (int)((cube->player.y / GRID_SIZE)
			- (cube->mini_map_grid_size / 2));
	vars->start_x = (int)((cube->player.x / GRID_SIZE)
			- (cube->mini_map_grid_size / 2));
	if (vars->start_y < 0)
		vars->start_y = 0;
	if (vars->start_x < 0)
		vars->start_x = 0;
	vars->end_y = vars->start_y + cube->mini_map_grid_size;
	vars->end_x = vars->start_x + cube->mini_map_grid_size;
	if (vars->end_y > cube->map_y)
		vars->end_y = cube->map_y;
	if (vars->end_x > cube->map_x)
		vars->end_x = cube->map_x;
}

void	draw_grid(t_cube *cube)
{
	t_vars13	vars;

	draw_grid1(cube, &vars);
	draw_grid2(cube, &vars);
	while (vars.y < vars.end_y)
	{
		vars.x = vars.start_x;
		while (vars.x < vars.end_x)
		{
			if (cube->map[vars.y][vars.x] == '1')
				draw_bg(cube, vars.x * GRID_SIZE, vars.y * GRID_SIZE,
					0x676767ff);
			else
				draw_bg(cube, vars.x * GRID_SIZE, vars.y * GRID_SIZE,
					0x969696ff);
			vars.x++;
		}
		vars.y++;
	}
}

void	draw_bg(t_cube *cube, int x, int y, uint32_t color)
{
	int		start_y;
	int		start_x;
	int		i;
	int		j;
	double	dst;

	start_y = (int)((cube->player.y) - (cube->mini_map_size / 2.0));
	start_x = (int)((cube->player.x) - (cube->mini_map_size / 2.0));
	i = 0;
	while (i < GRID_SIZE)
	{
		j = 0;
		while (j < GRID_SIZE)
		{
			dst = sqrt(((double)(x + i - start_x) - cube->mini_map_size / 2.0f)
					* ((double)(x + i - start_x) - cube->mini_map_size / 2.0f)
					+ ((double)(y + j - start_y) - cube->mini_map_size / 2.0f)
					* ((double)(y + j - start_y) - cube->mini_map_size / 2.0f));
			if (dst < 0.07 * cube->screen_width_buff)
				mlx_put_pixel(cube->image, x + i - start_x, y + j - start_y,
					color);
			j++;
		}
		i++;
	}
}
