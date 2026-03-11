/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:57 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 19:52:10 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	ft_enemy2(t_cube *cube, t_enemy *enemy, mlx_texture_t **texture,
		t_vars10 *vars)
{
	gettimeofday(&vars->tv, NULL);
	vars->current_time = (vars->tv.tv_sec * 1000) + (vars->tv.tv_usec / 1000);
	if (enemy->dead)
	{
		if (enemy->blood_frame_index >= 12)
			return (ft_health(cube, enemy), false);
		else if (vars->current_time - enemy->blood_time > BLOOD_ANIM_DELAY)
		{
			enemy->blood_time = vars->current_time;
			enemy->blood_frame_index++;
		}
		if (enemy->blood_frame_index < 12)
			*texture = cube->blood.frame[enemy->blood_frame_index];
		else
			return (false);
	}
	if (enemy->dead == false && enemy->hp <= 0)
	{
		*texture = cube->blood.frame[enemy->blood_frame_index];
		enemy->blood_time = vars->current_time;
		enemy->dead = true;
	}
	return (true);
}

bool	ft_enemy3(t_cube *cube, t_enemy *enemy, t_vars10 *vars)
{
	enemy->player_dst = sqrt((cube->player.x - enemy->x) * (cube->player.x
				- enemy->x) + (cube->player.y - enemy->y) * (cube->player.y
				- enemy->y));
	if (enemy->player_dst > MAX_DST)
		return (false);
	vars->player_dir = (t_vect2){(cube->player.x - enemy->x)
		/ enemy->player_dst, (cube->player.y - enemy->y) / enemy->player_dst, 0,
		0};
	vars->player_dir.x *= ENEMY_SPEED;
	vars->player_dir.y *= ENEMY_SPEED;
	if (enemy->dead == false && enemy->player_dst < MIN_ATK_DST)
	{
		if (enemy->delay == false)
		{
			printf("enemy has shot!\n");
			ft_init_projectile(cube, enemy, &vars->player_dir);
			if (cube->player.hp < 0)
				cube->player.hp = 0;
			enemy->atk_time = vars->tv.tv_sec;
			enemy->delay = true;
		}
	}
	return (true);
}

bool	ft_enemy4(t_cube *cube, t_enemy *enemy, t_vars10 *vars)
{
	if (enemy->delay == true)
	{
		if ((int)(vars->tv.tv_sec - enemy->atk_time) >= enemy->atk_delay)
			enemy->delay = false;
	}
	vars->angle_diff = atan2(enemy->y - cube->player.y, enemy->x
			- cube->player.x);
	vars->tetha_delta = vars->angle_diff - cube->player.angle;
	while (vars->tetha_delta > PI)
		vars->tetha_delta -= 2 * PI;
	while (vars->tetha_delta < -PI)
		vars->tetha_delta += 2 * PI;
	vars->midx = ((0.5 * cube->screen_width)) + (tan(vars->tetha_delta)
			* cube->proj_dst);
	vars->dst = sqrt((enemy->x - cube->player.x) * (enemy->x - cube->player.x)
			+ (enemy->y - cube->player.y) * (enemy->y - cube->player.y))
		* cos(vars->tetha_delta);
	if (vars->dst < 0.1)
		return (false);
	vars->tmp = 1.0 - (vars->dst / MAX_DST);
	if (vars->tmp > 1.0)
		vars->tmp = 1.0;
	else if (vars->tmp < 0.0)
		vars->tmp = 0.0;
	return (true);
}

bool	ft_enemy5(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture,
		t_vars10 *vars)
{
	vars->height = (GRID_SIZE / vars->dst) * cube->proj_dst;
	vars->scale_ratio = texture->height / vars->height;
	vars->proj_z_offset = (((GRID_SIZE / 2.0) - cube->camera_h) / vars->dst)
		* cube->proj_dst;
	vars->start_x = vars->midx - (texture->width / vars->scale_ratio) / 2;
	vars->start_y = ((cube->screen_height / 2.0) + cube->pitch
			- vars->proj_z_offset) - (texture->height / vars->scale_ratio) / 2;
	vars->const_y = vars->start_y;
	vars->end_x = vars->start_x + (texture->width / vars->scale_ratio);
	vars->end_y = vars->start_y + (texture->height / vars->scale_ratio);
	enemy->start_y = vars->start_y;
	enemy->end_y = vars->end_y;
	enemy->start_x = vars->start_x;
	enemy->end_x = vars->end_x;
	vars->tex_x = 0;
	vars->tex_y = 0;
	if (vars->start_x < 0)
	{
		vars->tex_x += (-vars->start_x) * vars->scale_ratio;
		vars->start_x = 0;
	}
	if (vars->start_x >= cube->screen_width)
		return (false);
	return (true);
}

void	ft_enemy(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture)
{
	t_vars10	vars;

	if (!ft_enemy2(cube, enemy, &texture, &vars) || !ft_enemy3(cube, enemy,
			&vars) || !ft_enemy4(cube, enemy, &vars) || !ft_enemy5(cube, enemy,
			texture, &vars))
		return ;
	if (vars.end_x > cube->screen_width)
		vars.end_x = cube->screen_width;
	if (vars.start_y < 0)
	{
		vars.tex_y = (-vars.start_y) * vars.scale_ratio;
		vars.start_y = 0;
	}
	if (vars.start_y >= cube->screen_height)
		return ;
	if (vars.end_x > cube->screen_width)
		vars.end_x = cube->screen_width;
	if (vars.end_y > cube->screen_height)
		vars.end_y = cube->screen_height;
	ft_enemy7(cube, texture, &vars);
}
