/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mouvement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:58 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 17:59:37 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_mouvement3(t_cube *cube, struct timeval *tv)
{
	cube->tilt_angle = ft_lerp_tilt(cube->target_angle, cube->tilt_angle);
	cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
	cube->player.current_speed_fb_x = ft_lerp_move(0.0,
			cube->player.current_speed_fb_x, 0.998);
	cube->player.current_speed_fb_y = ft_lerp_move(0.0,
			cube->player.current_speed_fb_y, 0.998);
	cube->player.current_speed_lr_x = ft_lerp_move(0.0,
			cube->player.current_speed_lr_x, 0.998);
	cube->player.current_speed_lr_y = ft_lerp_move(0.0,
			cube->player.current_speed_lr_y, 0.998);
	ft_mouvement_limits(cube, cube->player.x + cube->player.current_speed_fb_x
		+ cube->player.current_speed_lr_x, cube->player.y
		+ cube->player.current_speed_fb_y + cube->player.current_speed_lr_y);
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
		double *max_sin_speed)
{
	*max_cos_speed = cos(cube->player.angle) * cube->player.speed_mult
		* cube->mlx->delta_time;
	*max_sin_speed = sin(cube->player.angle) * cube->player.speed_mult
		* cube->mlx->delta_time;
	cube->player.dst_speed_lr_x = 0.0;
	cube->player.dst_speed_lr_y = 0.0;
	cube->player.dst_speed_fb_x = 0.0;
	cube->player.dst_speed_fb_y = 0.0;
	cube->target_angle = 0.0;
}

void	ft_mouvement5(t_cube *cube, double max_cos_speed, double max_sin_speed)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_D))
	{
		cube->player.dst_speed_lr_x = -1 * max_sin_speed;
		cube->player.dst_speed_lr_y = max_cos_speed;
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_A))
	{
		cube->player.dst_speed_lr_x = max_sin_speed;
		cube->player.dst_speed_lr_y = -1 * max_cos_speed;
	}
}

void	ft_mouvement6(t_cube *cube, double max_cos_speed, double max_sin_speed)
{
	if (mlx_is_key_down(cube->mlx, MLX_KEY_W))
	{
		cube->player.dst_speed_fb_x = max_cos_speed;
		cube->player.dst_speed_fb_y = max_sin_speed;
	}
	else if (mlx_is_key_down(cube->mlx, MLX_KEY_S))
	{
		cube->player.dst_speed_fb_x = -1 * max_cos_speed;
		cube->player.dst_speed_fb_y = -1 * max_sin_speed;
	}
}

void	ft_mouvement(t_cube *cube, double max_cos_speed, double max_sin_speed)
{
	ft_mouvement1(cube);
	ft_mouvement4(cube, &max_cos_speed, &max_sin_speed);
	ft_mouvement5(cube, max_cos_speed, max_sin_speed);
	ft_mouvement6(cube, max_cos_speed, max_sin_speed);
	cube->player.current_speed_fb_x = ft_lerp_speed(cube->player.dst_speed_fb_x,
			cube->player.current_speed_fb_x);
	cube->player.current_speed_fb_y = ft_lerp_speed(cube->player.dst_speed_fb_y,
			cube->player.current_speed_fb_y);
	cube->player.current_speed_lr_x = ft_lerp_speed(cube->player.dst_speed_lr_x,
			cube->player.current_speed_lr_x);
	cube->player.current_speed_lr_y = ft_lerp_speed(cube->player.dst_speed_lr_y,
			cube->player.current_speed_lr_y);
	ft_mouvement_limits(cube, cube->player.x + cube->player.current_speed_fb_x
		+ cube->player.current_speed_lr_x, cube->player.y
		+ cube->player.current_speed_fb_y + cube->player.current_speed_lr_y);
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}
