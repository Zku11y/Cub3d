/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:59 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 17:16:34 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_turn(t_cube *cube)
{
	if(mlx_is_key_down(cube->mlx, MLX_KEY_RIGHT)){
		cube->player.angle += cube->mouse_sens;
	}
	else if(mlx_is_key_down(cube->mlx, MLX_KEY_LEFT)){
		cube->player.angle -= cube->mouse_sens;		
	}
	// int			mouse_x;
	// int			mouse_y;
	// static int	frames = 5;

	// mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	// mouse_x = mouse_x - (cube->screen_width / 2);
	// mouse_y = mouse_y - (cube->screen_height / 2);
	// cube->player.angle += mouse_x * (cube->mouse_sens * 100)
	// 	/ (((double)cube->screen_height / 100)
	// 		* (cube->menu.settings.fov.max_fov - cube->fov
	// 			+ cube->menu.settings.fov.min_fov));
	// if (frames > 0)
	// 	frames--;
	// else
	// 	cube->pitch += (-1 * mouse_y) * ((cube->mouse_sens * 100));
	// if (cube->pitch > cube->pitch_max)
	// 	cube->pitch = cube->pitch_max;
	// if (cube->pitch < -cube->pitch_max)
	// 	cube->pitch = -cube->pitch_max;
	// mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height
	// 	/ 2);
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
		cube->player.current_speed_FB_X = 0;
		cube->player.current_speed_LR_X = 0;
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
		cube->player.current_speed_FB_Y = 0;
		cube->player.current_speed_LR_Y = 0;
	}
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}
