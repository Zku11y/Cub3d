/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:58 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 19:16:47 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mouvement3(t_cube *cube, struct timeval *tv)
{
	cube->tilt_angle = ft_lerp_tilt(cube->target_angle, cube->tilt_angle);
	cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
	cube->player.current_speed_FB_X = ft_lerp_move(0.0,
			cube->player.current_speed_FB_X, 0.998);
	cube->player.current_speed_FB_Y = ft_lerp_move(0.0,
			cube->player.current_speed_FB_Y, 0.998);
	cube->player.current_speed_LR_X = ft_lerp_move(0.0,
			cube->player.current_speed_LR_X, 0.998);
	cube->player.current_speed_LR_Y = ft_lerp_move(0.0,
			cube->player.current_speed_LR_Y, 0.998);
	ft_mouvement_limits(cube, cube->player.x + cube->player.current_speed_FB_X
		+ cube->player.current_speed_LR_X, cube->player.y
		+ cube->player.current_speed_FB_Y + cube->player.current_speed_LR_Y);
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& cube->player.delay == false)
	{
		gettimeofday(tv, NULL);
		cube->player.delay = true;
		cube->player.attacked = true;
		cube->player.atk_time = (*tv).tv_sec;
	}
}

void	ft_mouvement4(t_cube *cube, double *max_cos_speed,
		double *max_sin_speed, struct timeval *tv)
{
	if (!mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_CONTROL)
		&& cube->player.move_state != SPRINT)
	{
		cube->player.move_state = WALK;
		cube->player.dst_speed_mult = PLAYER_SPEED;
		cube->dst_camera_h = CAM_H;
	}
	*max_cos_speed = cos(cube->player.angle) * cube->player.speed_mult
		* cube->mlx->delta_time;
	*max_sin_speed = sin(cube->player.angle) * cube->player.speed_mult
		* cube->mlx->delta_time;
	cube->player.dst_speed_LR_X = 0.0;
	cube->player.dst_speed_LR_Y = 0.0;
	cube->player.dst_speed_FB_X = 0.0;
	cube->player.dst_speed_FB_Y = 0.0;
	cube->target_angle = 0.0;
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& cube->player.delay == false)
	{
		gettimeofday(tv, NULL);
		cube->player.delay = true;
		cube->player.attacked = true;
		cube->player.atk_time = (*tv).tv_sec;
	}
}

void	ft_mouvement5(t_cube *cube, double max_cos_speed, double max_sin_speed)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		cube->player.dst_speed_LR_X = -1 * max_sin_speed;
		cube->player.dst_speed_LR_Y = max_cos_speed;
		cube->target_angle = TILT_ANGLE;
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		cube->player.dst_speed_LR_X = max_sin_speed;
		cube->player.dst_speed_LR_Y = -1 * max_cos_speed;
		cube->target_angle = -TILT_ANGLE;
	}
}

void	ft_mouvement6(t_cube *cube, double max_cos_speed, double max_sin_speed)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		cube->player.weapon.move_lerp = ft_lerp_move(-cube->move_increase,
				cube->player.weapon.move_lerp, RECOIL_LERP);
		cube->player.dst_speed_FB_X = max_cos_speed;
		cube->player.dst_speed_FB_Y = max_sin_speed;
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		cube->player.weapon.move_lerp = ft_lerp_move(cube->move_increase,
				cube->player.weapon.move_lerp, RECOIL_LERP);
		cube->player.dst_speed_FB_X = -1 * max_cos_speed;
		cube->player.dst_speed_FB_Y = -1 * max_sin_speed;
	}
	else
	{
		cube->player.weapon.move_lerp = ft_lerp_move(0,
				cube->player.weapon.move_lerp, RECOIL_LERP);
	}
	cube->tilt_angle = ft_lerp_tilt(cube->target_angle, cube->tilt_angle);
	cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
}

void	ft_mouvement(t_cube *cube, double max_cos_speed, double max_sin_speed,
		struct timeval tv)
{
	ft_mouvement1(cube);
	if (mlx_is_key_down(cube->mlx, MLX_KEY_LEFT_CONTROL))
	{
		ft_mouvement2(cube);
		if (cube->player.move_state == SLIDE)
			return (ft_mouvement3(cube, &tv));
	}
	ft_mouvement4(cube, &max_cos_speed, &max_sin_speed, &tv);
	ft_mouvement5(cube, max_cos_speed, max_sin_speed);
	ft_mouvement6(cube, max_cos_speed, max_sin_speed);
	cube->player.current_speed_FB_X = ft_lerp_speed(cube->player.dst_speed_FB_X,
			cube->player.current_speed_FB_X);
	cube->player.current_speed_FB_Y = ft_lerp_speed(cube->player.dst_speed_FB_Y,
			cube->player.current_speed_FB_Y);
	cube->player.current_speed_LR_X = ft_lerp_speed(cube->player.dst_speed_LR_X,
			cube->player.current_speed_LR_X);
	cube->player.current_speed_LR_Y = ft_lerp_speed(cube->player.dst_speed_LR_Y,
			cube->player.current_speed_LR_Y);
	ft_mouvement_limits(cube, cube->player.x + cube->player.current_speed_FB_X
		+ cube->player.current_speed_LR_X, cube->player.y
		+ cube->player.current_speed_FB_Y + cube->player.current_speed_LR_Y);
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}
