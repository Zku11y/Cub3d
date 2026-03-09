/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:10 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 20:09:43 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_floor_ceiling1(t_cube *cube, t_vars9 *vars)
{
	vars->DirX = cos(cube->player.angle);
	vars->DirY = sin(cube->player.angle);
	vars->PlaneX = -vars->DirY * (cube->half_fov_rad);
	vars->PlaneY = vars->DirX * (cube->half_fov_rad);
	vars->RayDirL = (t_vect2){vars->DirX - vars->PlaneX, vars->DirY
		- vars->PlaneY, 0, 0};
	vars->RayDirR = (t_vect2){vars->DirX + vars->PlaneX, vars->DirY
		+ vars->PlaneY, 0, 0};
	vars->mid_point = (cube->screen_height / 2.0) + cube->pitch;
	vars->cam_height = cube->camera_h;
	vars->p = 0;
	vars->i = 0;
}

void	ft_floor_ceiling2(t_cube *cube, t_vars9 *vars)
{
	if (vars->i < vars->mid_point)
	{
		vars->p = (vars->mid_point) - (float)vars->i;
		vars->tex = cube->texture3;
		vars->cam_height = GRID_SIZE - (cube->camera_h);
	}
	else
	{
		vars->p = (float)vars->i - (vars->mid_point);
		vars->tex = cube->texture2;
		vars->cam_height = cube->camera_h;
	}
	if (vars->p == 0.0)
		vars->p = 1.0;
	vars->rowDst = (vars->cam_height * cube->proj_dst) / vars->p;
	vars->floorL = (t_vect2){(cube->player.x) + vars->rowDst * vars->RayDirL.x,
		(cube->player.y) + vars->rowDst * vars->RayDirL.y, 0, 0};
	vars->floorR = (t_vect2){(cube->player.x) + vars->rowDst * vars->RayDirR.x,
		(cube->player.y) + vars->rowDst * vars->RayDirR.y, 0, 0};
	vars->step = (t_vect2){(vars->floorR.x - vars->floorL.x)
		/ cube->screen_width, (vars->floorR.y - vars->floorL.y)
		/ cube->screen_width, 0, 0};
	vars->ft_floor = (t_vect2){vars->floorL.x, vars->floorL.y, 0, 0};
	// vars->tmp = 1.0 - (vars->rowDst / MAX_DST);
}

void	ft_floor_ceiling3(t_cube *cube, t_vars9 *vars)
{
	double dx;
	double dy;
	double dist;

	vars->fracX = fmod(vars->ft_floor.x / GRID_SIZE, 1.0);
	vars->fracY = fmod(vars->ft_floor.y / GRID_SIZE, 1.0);
	if (vars->fracX < 0)
		vars->fracX += 1.0;
	if (vars->fracY < 0)
		vars->fracY += 1.0;
	vars->texX = (int)(vars->fracX * vars->tex->width);
	vars->texY = (int)(vars->fracY * vars->tex->height);
	vars->k = ((vars->tex->bytes_per_pixel * vars->texY * vars->tex->width)
			+ (vars->texX * vars->tex->bytes_per_pixel));

	dx = vars->ft_floor.x - cube->player.x;
    dy = vars->ft_floor.y - cube->player.y;
    dist = sqrt((dx * dx) + (dy * dy));

    vars->tmp = 1.0 - (dist / MAX_DST);
    if (vars->tmp > 1.0)
        vars->tmp = 1.0;
    else if (vars->tmp < 0.0)
        vars->tmp = 0.0;			

	vars->r = (vars->tex->pixels[vars->k + 0] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	vars->g = (vars->tex->pixels[vars->k + 1] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	vars->b = (vars->tex->pixels[vars->k + 2] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	vars->a = vars->tex->pixels[vars->k + 3];
	vars->y_iter = cube->screen_width * vars->i * 4;
	vars->coords = (t_vect2){vars->j, vars->i, 0, 0};
	vars->iter = 0;
}

void	ft_floor_ceiling4(t_cube *cube, t_vars9 *vars)
{
	while (vars->iter < cube->line_girth)
	{
		if (!check_screen_limits(cube, vars->coords))
		{
			cube->prev_buffer[(vars->y_iter) + (vars->j * 4) + 0] = vars->r;
			cube->prev_buffer[(vars->y_iter) + (vars->j * 4) + 1] = vars->g;
			cube->prev_buffer[(vars->y_iter) + (vars->j * 4) + 2] = vars->b;
			cube->prev_buffer[(vars->y_iter) + (vars->j * 4) + 3] = vars->a;
		}
		vars->ft_floor.x += vars->step.x;
		vars->ft_floor.y += vars->step.y;
		vars->j++;
		vars->iter++;
	}
}

void	ft_floor_ceiling(t_cube *cube)
{
	t_vars9	vars;

	ft_floor_ceiling1(cube, &vars);
	while (vars.i < cube->screen_height)
	{
		ft_floor_ceiling2(cube, &vars);
		// if (vars.tmp > 1.0)
		// 	vars.tmp = 1.0;
		// else if (vars.tmp < 0.0)
		// 	vars.tmp = 0.0;
		vars.j = 0;
		while (vars.j < cube->screen_width)
		{
			ft_floor_ceiling3(cube, &vars);
			ft_floor_ceiling4(cube, &vars);
		}
		vars.i++;
	}
}
