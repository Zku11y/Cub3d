/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projectile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:00 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 22:42:27 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_projectile2(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	if (projectile->in_use == 0)
		return (false);
	vars->player_dst = sqrt((cube->player.x - projectile->x) * (cube->player.x
				- projectile->x) + (cube->player.y - projectile->y)
			* (cube->player.y - projectile->y));
	if (vars->player_dst < HITBOX_DST)
	{
		cube->player.HP -= projectile->DMG;
		cube->player.hit = true;
		projectile->in_use = 0;
		return (false);
	}
	if (cube->map[(int)((projectile->y + (projectile->dir.y
					* projectile->speed)) / GRID_SIZE)][(int)(projectile->x
			/ GRID_SIZE)] == '1')
		return ((projectile->in_use = 0), false);
	if (cube->map[(int)(projectile->y / GRID_SIZE)][(int)((projectile->x
				+ (projectile->dir.x * projectile->speed)) / GRID_SIZE)] == '1')
		return ((projectile->in_use = 0), false);
	projectile->y += projectile->dir.y * projectile->speed;
	projectile->x += projectile->dir.x * projectile->speed;
	vars->angle_diff = atan2(projectile->y - cube->player.y, projectile->x
			- cube->player.x);
	vars->tetha_delta = vars->angle_diff - cube->player.angle;
	return (true);
}

bool	ft_projectile3(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	while (vars->tetha_delta > PI)
		vars->tetha_delta -= 2 * PI;
	while (vars->tetha_delta < -PI)
		vars->tetha_delta += 2 * PI;
	vars->midX = ((0.5 * cube->screen_width)) + (tan(vars->tetha_delta)
			* cube->proj_dst);
	vars->dst = sqrt((projectile->x - cube->player.x) * (projectile->x
				- cube->player.x) + (projectile->y - cube->player.y)
			* (projectile->y - cube->player.y)) * cos(vars->tetha_delta);
	if (vars->dst < 0.1)
		return (false);
	vars->tmp = 1.0 - (vars->dst / MAX_DST);
	if (vars->tmp > 1.0)
		vars->tmp = 1.0;
	else if (vars->tmp < 0.0)
		vars->tmp = 0.0;
	vars->height = (GRID_SIZE / vars->dst) * cube->proj_dst;
	vars->scale_ratio = projectile->texture->height / vars->height;
	vars->proj_z_offset = (((GRID_SIZE / 2.0) - cube->camera_h) / vars->dst)
		* cube->proj_dst;
	vars->start_x = vars->midX - (projectile->texture->width
			/ vars->scale_ratio) / 2;
	return (true);
}

bool	ft_projectile4(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	vars->start_y = ((cube->screen_height / 2.0) + cube->pitch
			- vars->proj_z_offset) - (projectile->texture->height
			/ vars->scale_ratio) / 2;
	vars->const_y = vars->start_y;
	vars->end_x = vars->start_x + (projectile->texture->width
			/ vars->scale_ratio);
	vars->end_y = vars->start_y + (projectile->texture->height
			/ vars->scale_ratio);
	vars->tex_x = 0;
	vars->tex_y = 0;
	if (vars->start_x < 0)
	{
		vars->tex_x += (-vars->start_x) * vars->scale_ratio;
		vars->start_x = 0;
	}
	if (vars->start_x >= cube->screen_width)
		return (false);
	if (vars->end_x > cube->screen_width)
		vars->end_x = cube->screen_width;
	if (vars->start_y < 0)
	{
		vars->tex_y = (-vars->start_y) * vars->scale_ratio;
		vars->start_y = 0;
	}
	return (true);
}

void	ft_projectile5(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	if (vars->y < 0)
		vars->y = 0;
	if (!check_screen_limits(cube, (t_vect2){vars->start_x, vars->start_y, 0,
			0}))
	{
		vars->k = (vars->x * projectile->texture->bytes_per_pixel)
			+ (projectile->texture->width * projectile->texture->bytes_per_pixel
				* vars->y);
		if (projectile->texture->pixels[vars->k + 3] > 128)
		{
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4)
				+ 0] = (projectile->texture->pixels[vars->k + 0] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4)
				+ 1] = (projectile->texture->pixels[vars->k + 1] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4)
				+ 2] = (projectile->texture->pixels[vars->k + 2] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4)
				+ 3] = projectile->texture->pixels[vars->k + 3];
		}
	}
	vars->start_y++;
}

void	ft_projectile6(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	while (vars->start_x < vars->end_x)
	{
		vars->start_y = vars->const_y;
		vars->x = (int)vars->tex_x;
		if (vars->x >= (int)projectile->texture->width)
			vars->x = projectile->texture->width - 1;
		if (vars->x < 0)
			vars->x = 0;
		vars->tex_y = 0;
		if (cube->z_buffer[vars->start_x] > vars->dst)
		{
			cube->z_buffer[vars->start_x] = vars->dst;
			while (vars->start_y < vars->end_y)
			{
				vars->y = (int)vars->tex_y;
				if (vars->y >= (int)projectile->texture->height)
					vars->y = projectile->texture->height - 1;
				ft_projectile5(cube, projectile, vars);
				vars->tex_y += vars->scale_ratio;
			}
		}
		vars->tex_x += vars->scale_ratio;
		vars->start_x++;
	}
}
