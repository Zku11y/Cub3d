/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:15 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 18:01:21 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_ups2(t_cube *cube, t_vars8 *vars)
{
	if (cube->state == GAME)
	{
		vars->prev = (uint32_t *)cube->new_buffer;
		vars->screen_h = cube->screen_height - (cube->tilt_addition_height * 2);
		vars->screen_w = cube->screen_width - (cube->tilt_addition_width * 2);
	}
	vars->iter_x = (double)vars->screen_w / (double)cube->screen_width_buff;
	vars->iter_y = (double)vars->screen_h / (double)cube->screen_height_buff;
	vars->prev_x = 0.0;
	vars->prev_y = 0.0;
	vars->new_x = 0;
	vars->new_y = 0;
}

void	ft_ups(t_cube *cube, mlx_image_t *image)
{
	t_vars8	vars;

	vars.new = (uint32_t *)image->pixels;
	vars.prev = (uint32_t *)cube->prev_buffer;
	vars.screen_h = cube->screen_height;
	vars.screen_w = cube->screen_width;
	ft_ups2(cube, &vars);
	while (vars.new_y < cube->screen_height_buff && vars.prev_y < vars.screen_h)
	{
		vars.new_x = 0;
		vars.prev_x = 0.0;
		while (vars.new_x < cube->screen_width_buff
			&& vars.prev_x < vars.screen_w)
		{
			vars.new[(vars.new_y * cube->screen_width_buff)
				+ vars.new_x] = vars.prev[((int)vars.prev_y * vars.screen_w)
				+ (int)vars.prev_x];
			vars.new_x++;
			vars.prev_x += vars.iter_x;
		}
		vars.new_y++;
		vars.prev_y += vars.iter_y;
	}
}

void	ft_draw_world2(t_cube *cube, int i, t_vect2 *start, t_vect2 *end)
{
	int		j;
	double	length;
	double	proj_z_offset;
	double	len;

	j = 0;
	length = cube->rays[i].length * cos(cube->rays[i].real_angle
			- cube->player.angle);
	len = ((GRID_SIZE) / length) * cube->proj_dst;
	proj_z_offset = (((GRID_SIZE / 2.0) - (cube->camera_h)) / length)
		* cube->proj_dst;
	start->y = ((cube->screen_height - len) / 2) + cube->pitch - proj_z_offset;
	end->x = start->x;
	end->y = start->y + len;
	while (j < cube->line_girth)
	{
		if ((int)start->x < cube->screen_width)
			cube->z_buffer[(int)start->x] = length;
		ft_draw_texture(cube, &cube->rays[i], *start, *end);
		start->x++;
		end->x++;
		j++;
	}
}

void	ft_draw_world(t_cube *cube)
{
	t_vect2	start;
	t_vect2	end;
	int		i;

	start.x = (cube->screen_width - (cube->line_girth * cube->res)) / 2;
	i = 0;
	while (i <= cube->res)
	{
		ft_draw_world2(cube, i, &start, &end);
		i++;
	}
}

void	ft_draw_rays(t_cube *cube)
{
	t_vars12	vars;

	vars.dirx = cos(cube->player.angle);
	vars.diry = sin(cube->player.angle);
	vars.planex = -vars.diry * cube->half_fov_rad;
	vars.planey = vars.dirx * cube->half_fov_rad;
	vars.i = 0;
	while (vars.i < cube->res)
	{
		vars.camerax = 2.0 * vars.i / (double)cube->res - 1.0;
		vars.raydirx = vars.dirx + vars.planex * vars.camerax;
		vars.raydiry = vars.diry + vars.planey * vars.camerax;
		vars.rayangle = atan2(vars.raydiry, vars.raydirx);
		if (vars.rayangle < 0)
			vars.rayangle += 2 * PI;
		else if (vars.rayangle > 2 * PI)
			vars.rayangle -= 2 * PI;
		cube->rays[vars.i].real_angle = vars.rayangle;
		ft_ray_init(cube, &(cube->rays[vars.i]), vars.rayangle);
		vars.i++;
	}
}
