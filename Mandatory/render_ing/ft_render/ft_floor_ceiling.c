/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:10 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 20:11:54 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_floor_ceiling1(t_cube *cube, t_vars9 *vars)
{
	vars->dirx = cos(cube->player.angle);
	vars->diry = sin(cube->player.angle);
	vars->planex = -vars->diry * (cube->half_fov_rad);
	vars->planey = vars->dirx * (cube->half_fov_rad);
	vars->raydirl = (t_vect2){vars->dirx - vars->planex, vars->diry
		- vars->planey, 0, 0};
	vars->raydirr = (t_vect2){vars->dirx + vars->planex, vars->diry
		+ vars->planey, 0, 0};
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
	vars->rowdst = (vars->cam_height * cube->proj_dst) / vars->p;
	vars->floorl = (t_vect2){(cube->player.x) + vars->rowdst * vars->raydirl.x,
		(cube->player.y) + vars->rowdst * vars->raydirl.y, 0, 0};
	vars->floorr = (t_vect2){(cube->player.x) + vars->rowdst * vars->raydirr.x,
		(cube->player.y) + vars->rowdst * vars->raydirr.y, 0, 0};
	vars->step = (t_vect2){(vars->floorr.x - vars->floorl.x)
		/ cube->screen_width, (vars->floorr.y - vars->floorl.y)
		/ cube->screen_width, 0, 0};
	vars->ft_floor = (t_vect2){vars->floorl.x, vars->floorl.y, 0, 0};
	vars->tmp = 1.0 - (vars->rowdst / MAX_DST);
}

void	ft_floor_ceiling3(t_cube *cube, t_vars9 *vars)
{
	vars->fracx = fmod(vars->ft_floor.x / GRID_SIZE, 1.0);
	vars->fracy = fmod(vars->ft_floor.y / GRID_SIZE, 1.0);
	if (vars->fracx < 0)
		vars->fracx += 1.0;
	if (vars->fracy < 0)
		vars->fracy += 1.0;
	vars->texx = (int)(vars->fracx * vars->tex->width);
	vars->texy = (int)(vars->fracy * vars->tex->height);
	vars->k = ((vars->tex->bytes_per_pixel * vars->texy * vars->tex->width)
			+ (vars->texx * vars->tex->bytes_per_pixel));
	vars->r = vars->tex->pixels[vars->k + 0] * (vars->tmp);
	vars->g = vars->tex->pixels[vars->k + 1] * (vars->tmp);
	vars->b = vars->tex->pixels[vars->k + 2] * (vars->tmp);
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
		if (vars.tmp > 1.0)
			vars.tmp = 1.0;
		else if (vars.tmp < 0.0)
			vars.tmp = 0.0;
		vars.j = 0;
		while (vars.j < cube->screen_width)
		{
			ft_floor_ceiling3(cube, &vars);
			ft_floor_ceiling4(cube, &vars);
		}
		vars.i++;
	}
}
