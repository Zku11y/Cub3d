/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_health.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:54 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 01:07:23 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_health4(t_cube *cube, mlx_texture_t *texture, t_vars10 *vars)
{
	vars->k = (vars->x * texture->bytes_per_pixel) + (texture->width
			* texture->bytes_per_pixel * vars->y);
	if (texture->pixels[vars->k + 3] > 128
		&& cube->z_buffer[vars->start_x] >= vars->dst)
	{
		cube->z_buffer[vars->start_x] = vars->dst;
		cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
			+ ((int)vars->start_x * 4) + 0] = texture->pixels[vars->k + 0]
			* vars->tmp;
		cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
			+ ((int)vars->start_x * 4) + 1] = texture->pixels[vars->k + 1]
			* vars->tmp;
		cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
			+ ((int)vars->start_x * 4) + 2] = texture->pixels[vars->k + 2]
			* vars->tmp;
		cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
			+ ((int)vars->start_x * 4) + 3] = texture->pixels[vars->k + 3];
	}
}

void	ft_health5(t_cube *cube, mlx_texture_t *texture, t_vars10 *vars)
{
	vars->start_y = vars->const_y;
	vars->x = (int)vars->tex_x;
	if (vars->x >= (int)texture->width)
		vars->x = texture->width - 1;
	if (vars->x < 0)
		vars->x = 0;
	vars->tex_y = 0;
	if (cube->z_buffer[vars->start_x] > vars->dst)
	{
		while (vars->start_y < vars->end_y)
		{
			vars->y = (int)vars->tex_y;
			if (vars->y >= (int)texture->height)
				vars->y = texture->height - 1;
			if (vars->y < 0)
				vars->y = 0;
			if (!check_screen_limits(cube, (t_vect2){vars->start_x,
					vars->start_y, 0, 0}))
				ft_health4(cube, texture, vars);
			vars->start_y++;
			vars->tex_y += vars->scale_ratio;
		}
	}
	vars->tex_x += vars->scale_ratio;
	vars->start_x++;
}

bool	ft_health6(t_cube *cube, mlx_texture_t *texture, t_enemy *enemy,
		t_vars10 *vars)
{
	vars->player_dst = sqrt((cube->player.x - vars->pos_x) * (cube->player.x
				- vars->pos_x) + (cube->player.y - vars->pos_y)
			* (cube->player.y - vars->pos_y));
	if (!ft_health2(cube, enemy, vars))
		return (false);
	ft_health3(cube, texture, enemy, vars);
	if (vars->start_x >= cube->screen_width)
		return (false);
	if (vars->end_x > cube->screen_width)
		vars->end_x = cube->screen_width;
	if (vars->start_y < 0)
	{
		vars->tex_y = (-vars->start_y) * vars->scale_ratio;
		vars->start_y = 0;
	}
	if (vars->start_y >= cube->screen_height)
		return (false);
	if (vars->end_x > cube->screen_width)
		vars->end_x = cube->screen_width;
	if (vars->end_y > cube->screen_height)
		vars->end_y = cube->screen_height;
	return (true);
}

bool	ft_health2(t_cube *cube, t_enemy *enemy, t_vars10 *vars)
{
	if (vars->player_dst < HITBOX_DST)
	{
		cube->flash.r = 0.2;
		cube->flash.g = 3.0;
		cube->flash.b = 0.2;
		cube->player.HP += 50;
		if (cube->player.HP > MAX_HP)
			cube->player.HP = MAX_HP;
		return (enemy->health_spawn = false, false);
	}
	vars->angle_diff = atan2(vars->pos_y - cube->player.y, vars->pos_x
			- cube->player.x);
	vars->tetha_delta = vars->angle_diff - cube->player.angle;
	while (vars->tetha_delta > PI)
		vars->tetha_delta -= 2 * PI;
	while (vars->tetha_delta < -PI)
		vars->tetha_delta += 2 * PI;
	vars->midX = ((0.5 * cube->screen_width)) + (tan(vars->tetha_delta)
			* cube->proj_dst);
	vars->dst = sqrt((vars->pos_x - cube->player.x) * (vars->pos_x
				- cube->player.x) + (vars->pos_y - cube->player.y)
			* (vars->pos_y - cube->player.y)) * cos(vars->tetha_delta);
	if (vars->dst < 0.1)
		return (false);
	return (true);
}

void	ft_health(t_cube *cube, t_enemy *enemy)
{
	t_vars10	vars;

	vars.pos_x = enemy->x;
	vars.pos_y = enemy->y;
	if (enemy->health_spawn == false)
		return ;
	if (enemy->health_animation == 0)
	{
		enemy->health_offset += 0.15;
		if (enemy->health_offset >= 10)
			enemy->health_animation = 1;
	}
	else if (enemy->health_animation == 1)
	{
		enemy->health_offset -= 0.15;
		if (enemy->health_offset <= -10)
			enemy->health_animation = 0;
	}
	if (!ft_health6(cube, enemy->health, enemy, &vars))
		return ;
	while (vars.start_x < vars.end_x)
		ft_health5(cube, enemy->health, &vars);
}
