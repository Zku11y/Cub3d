/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heart.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:56 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 01:07:09 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_heart(t_cube *cube)
{
	if ((double)cube->player.HP > (0.8 * (double)MAX_HP))
		return ((void)(cube->heart.blur_lerp = BLUR_LERP));
	else if ((double)cube->player.HP > (0.6 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.8 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_1, 0, 0);
		cube->heart.blur_lerp = 0.4;
	}
	else if ((double)cube->player.HP > (0.4 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.6 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_2, 0, 0);
		cube->heart.blur_lerp = 0.3;
	}
	else if ((double)cube->player.HP > (0.2 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.4 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_3, 0, 0);
		cube->heart.blur_lerp = 0.2;
	}
	else
	{
		ft_prev_renderer(cube, cube->heart.frame_4, 0, 0);
		cube->heart.blur_lerp = 0.1;
	}
}

void	ft_health3(t_cube *cube, mlx_texture_t *texture, t_enemy *enemy,
		t_vars10 *vars)
{
	vars->tmp = 1.0 - (vars->dst / MAX_DST);
	if (vars->tmp > 1.0)
		vars->tmp = 1.0;
	else if (vars->tmp < 0.0)
		vars->tmp = 0.0;
	vars->height = (GRID_SIZE / vars->dst) * cube->proj_dst;
	vars->scale_ratio = texture->height / vars->height;
	vars->proj_z_offset = (((GRID_SIZE / 2.0) - cube->camera_h) / vars->dst)
		* cube->proj_dst;
	vars->start_x = vars->midX - (texture->width / vars->scale_ratio) / 2;
	vars->start_y = ((cube->screen_height / 2.0) + cube->pitch
			+ enemy->health_offset - vars->proj_z_offset) - (texture->height
			/ vars->scale_ratio) / 2;
	vars->const_y = vars->start_y;
	vars->end_x = vars->start_x + (texture->width / vars->scale_ratio);
	vars->end_y = vars->start_y + (texture->height / vars->scale_ratio);
	vars->tex_x = 0;
	vars->tex_y = 0;
	if (vars->start_x < 0)
	{
		vars->tex_x += (-vars->start_x) * vars->scale_ratio;
		vars->start_x = 0;
	}
}

void	ft_doors(t_cube *cube)
{
	double	dx;
	double	dy;
	double	player_dst_1;
	double	player_dst_2;

	dx = cube->player.x - ((cube->nu->start->d_x * GRID_SIZE) + (GRID_SIZE
				/ 2.0));
	dy = cube->player.y - ((cube->nu->start->d_y * GRID_SIZE) + (GRID_SIZE
				/ 2.0));
	player_dst_1 = sqrt((dx * dx) + (dy * dy));
	dx = cube->player.x - ((cube->nu->end->d_x * GRID_SIZE) + (GRID_SIZE
				/ 2.0));
	dy = cube->player.y - ((cube->nu->end->d_y * GRID_SIZE) + (GRID_SIZE
				/ 2.0));
	player_dst_2 = sqrt((dx * dx) + (dy * dy));
	if (player_dst_1 < 30.0)
		cube->nu->map[cube->nu->start->d_y][cube->nu->start->d_x] = '0';
	else
		cube->nu->map[cube->nu->start->d_y][cube->nu->start->d_x] = 'D';
	if (player_dst_2 < 30.0)
		cube->nu->map[cube->nu->end->d_y][cube->nu->end->d_x] = '0';
	else
		cube->nu->map[cube->nu->end->d_y][cube->nu->end->d_x] = 'D';
}

void	ft_mouvement1(t_cube *cube)
{
	ft_turn(cube);
	ft_angle_limit(&cube->player.angle);
	ft_doors(cube);
	cube->camera_h = ft_lerp_move(cube->dst_camera_h, cube->camera_h, 0.85);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_SHIFT)
		&& cube->player.move_state == WALK && (mlx_is_key_down(cube->mlx,
				MLX_KEY_A) || mlx_is_key_down(cube->mlx, MLX_KEY_D)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_W)
			|| mlx_is_key_down(cube->mlx, MLX_KEY_S)))
	{
		cube->player.dst_speed_mult = 1.5 * PLAYER_SPEED;
		cube->player.move_state = SPRINT;
	}
	cube->player.speed_mult = ft_lerp_move(cube->player.dst_speed_mult,
			cube->player.speed_mult, 0.9);
	if (cube->player.move_state == SPRINT && !mlx_is_key_down(cube->mlx,
			MLX_KEY_LEFT_SHIFT))
	{
		cube->player.dst_speed_mult = PLAYER_SPEED;
		cube->player.move_state = WALK;
	}
}

void	ft_mouvement2(t_cube *cube)
{
	if (cube->player.move_state == WALK || cube->player.move_state == SPRINT)
	{
		if ((int)(cube->player.current_speed_FB_X * 10.0) != 0
			|| (int)(cube->player.current_speed_LR_X * 10.0) != 0
			|| (int)(cube->player.current_speed_FB_Y * 10.0) != 0
			|| (int)(cube->player.current_speed_LR_Y * 10.0) != 0)
		{
			cube->player.current_speed_FB_X *= 1.5;
			cube->player.current_speed_FB_Y *= 1.5;
			cube->player.current_speed_LR_X *= 1.5;
			cube->player.current_speed_LR_Y *= 1.5;
			cube->player.move_state = SLIDE;
			cube->dst_camera_h = CAM_H / 2.0;
		}
	}
}
