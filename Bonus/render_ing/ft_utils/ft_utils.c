/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:46 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 23:10:46 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_fov_mod(t_cube *cube)
{
	int	dst_fov;

	if (cube->fov != cube->prev_fov)
	{
		cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0)
				* RADIANT_RATE);
		cube->half_fov_rad = tan((cube->fov / 2.0) * RADIANT_RATE);
		cube->prev_fov = cube->fov;
		cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
	}
	if (cube->player.move_state == WALK)
		cube->fov = ft_lerp_fov(cube->init_fov, cube->fov, FOV_LERP);
	else
	{
		dst_fov = 1.5 * cube->init_fov;
		if (dst_fov > 170)
			dst_fov = 170;
		cube->fov = ft_lerp_fov(dst_fov, cube->fov, 0.04);
	}
}

void	draw_crosshair2(t_cube *cube, t_vars7 *vars)
{
	while (++(vars->x) < cube->screen_width_buff)
	{
		vars->tex_x = (double)(vars->x) * ((double)(cube->crosshair->width)
				/ (double)(cube->screen_width_buff));
		vars->pixel_cords = ((vars->y) * 4 * cube->screen_width_buff)
			+ ((vars->x) * 4);
		vars->title_cords = (vars->tex_y * 4 * cube->crosshair->width)
			+ (vars->tex_x * 4);
		if (vars->tex_x >= (int)cube->crosshair->width
			|| vars->tex_y >= (int)cube->crosshair->height
			|| cube->crosshair->pixels[vars->tex_y * 4 * cube->crosshair->width
				+ vars->tex_x * 4 + 3] < 127)
			continue ;
		cube->image->pixels[vars->pixel_cords
			+ 0] = cube->crosshair->pixels[vars->title_cords + 0];
		cube->image->pixels[vars->pixel_cords
			+ 1] = cube->crosshair->pixels[vars->title_cords + 1];
		cube->image->pixels[vars->pixel_cords
			+ 2] = cube->crosshair->pixels[vars->title_cords + 2];
		cube->image->pixels[vars->pixel_cords
			+ 3] = cube->crosshair->pixels[vars->title_cords + 3];
	}
}

void	draw_crosshair(t_cube *cube)
{
	t_vars7	vars;

	vars.x = 0;
	vars.y = 0;
	while (vars.y < cube->screen_height_buff)
	{
		vars.x = -1;
		vars.tex_y = (double)(vars.y) *((double)(cube->crosshair->height)
				/ (double)(cube->screen_height_buff));
		draw_crosshair2(cube, &vars);
		vars.y++;
	}
}

bool	is_looking(t_cube *cube, t_enemy *enemy)
{
	if (enemy->dead == true)
		return (false);
	if ((enemy->start_x < cube->screen_width / 2)
		&& (enemy->end_x > cube->screen_width / 2)
		&& (enemy->start_y < cube->screen_height / 2)
		&& (enemy->end_y > cube->screen_height / 2))
		return (true);
	return (false);
}

void	set_screen_limits(t_cube *cube, t_vect2 *len)
{
	if (len->x > cube->screen_width)
		len->x = cube->screen_width;
	else if (len->x < 0)
		len->x = 0;
	if (len->y > cube->screen_height)
		len->y = cube->screen_height;
	else if (len->y < 0)
		len->y = 0;
}
