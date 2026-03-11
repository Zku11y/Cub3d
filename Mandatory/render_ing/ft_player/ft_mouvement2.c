/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:59 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 17:58:41 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_turn(t_cube *cube)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT))
	{
		cube->player.angle += cube->mouse_sens;
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT))
	{
		cube->player.angle -= cube->mouse_sens;
	}
}

void	ft_mouvement_limits2(t_cube *cube, double *check_x, double *new_x,
		int *grid_x)
{
	*check_x = *new_x;
	if (*new_x > cube->player.x)
		*check_x = *new_x + WALL_DST;
	else if (*new_x < cube->player.x)
		*check_x = *new_x - WALL_DST;
	*grid_x = (int)(*check_x / GRID_SIZE);
	if (cube->map[cube->player.grid_y][*grid_x] != '1')
	{
		cube->player.x = *new_x;
	}
	else
	{
		if (*new_x > cube->player.x)
			cube->player.x = ((cube->player.grid_x + 1) * GRID_SIZE) - WALL_DST;
		else
			cube->player.x = ((cube->player.grid_x) * GRID_SIZE) + WALL_DST;
		cube->player.current_speed_fb_x = 0;
		cube->player.current_speed_lr_x = 0;
	}
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
}

void	ft_mouvement_limits(t_cube *cube, double new_x, double new_y)
{
	double	check_x;
	double	check_y;

	int (grid_x), (grid_y);
	ft_mouvement_limits2(cube, &check_x, &new_x, &grid_x);
	check_y = new_y;
	if (new_y > cube->player.y)
		check_y = new_y + WALL_DST;
	else if (new_y < cube->player.y)
		check_y = new_y - WALL_DST;
	grid_y = (int)(check_y / GRID_SIZE);
	if (cube->map[grid_y][cube->player.grid_x] != '1')
	{
		cube->player.y = new_y;
	}
	else
	{
		if (new_y > cube->player.y)
			cube->player.y = ((cube->player.grid_y + 1) * GRID_SIZE) - WALL_DST;
		else
			cube->player.y = ((cube->player.grid_y) * GRID_SIZE) + WALL_DST;
		cube->player.current_speed_fb_y = 0;
		cube->player.current_speed_lr_y = 0;
	}
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}
