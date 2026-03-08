/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tilt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:19 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:14:21 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_tilt_2(t_cube *cube)
{
	if (!cube->flash.flashed && (cube->player.delay == true
			|| cube->player.hit == true))
	{
		if (cube->player.delay == true)
		{
			cube->flash.r = 2.0;
			cube->flash.g = 2.0;
			cube->flash.b = 2.0;
		}
		else
		{
			cube->flash.r = 3.0;
			cube->flash.g = 0.2;
			cube->flash.b = 0.2;
		}
		cube->flash.flashed = true;
		cube->player.hit = false;
	}
	if (cube->flash.flashed && cube->player.delay == false)
		cube->flash.flashed = false;
	cube->flash.r = ft_lerp_fov(cube->flash.dst_r, cube->flash.r, FLASH_LERP);
	cube->flash.g = ft_lerp_fov(cube->flash.dst_g, cube->flash.g, FLASH_LERP);
	cube->flash.b = ft_lerp_fov(cube->flash.dst_b, cube->flash.b, FLASH_LERP);
}

void	ft_tilt_3(t_cube *cube, int new_dst, int prev_dst)
{
	cube->new_buffer[new_dst + 0] = (uint8_t)cube->prev_buffer[prev_dst + 0]
		* cube->flash.r;
	if ((uint8_t)cube->prev_buffer[prev_dst + 0] * cube->flash.r > 255)
		cube->new_buffer[new_dst + 0] = (uint8_t)255;
	cube->new_buffer[new_dst + 1] = (uint8_t)cube->prev_buffer[prev_dst + 1]
		* cube->flash.g;
	if ((uint8_t)cube->prev_buffer[prev_dst + 1] * cube->flash.g > 255)
		cube->new_buffer[new_dst + 1] = (uint8_t)255;
	cube->new_buffer[new_dst + 2] = (uint8_t)cube->prev_buffer[prev_dst + 2]
		* cube->flash.b;
	if ((uint8_t)cube->prev_buffer[prev_dst + 2] * cube->flash.b > 255)
		cube->new_buffer[new_dst + 2] = (uint8_t)255;
	cube->new_buffer[new_dst + 3] = (uint8_t)cube->prev_buffer[prev_dst + 3];
}

void	ft_tilt(t_cube *cube)
{
	t_vars4	vars;

	gettimeofday(&vars.tv, NULL);
	vars.time = (vars.tv.tv_sec * 1000) + (vars.tv.tv_usec / 1000);
	vars.max_new_x = cube->screen_width - (cube->tilt_addition_width * 2);
	vars.max_new_y = cube->screen_height - (cube->tilt_addition_height * 2);
	ft_tilt_2(cube);
	vars.x = 0;
	while (vars.x++ < vars.max_new_x)
	{
		vars.y = 0;
		vars.prev_x = (double)vars.x + cube->tilt_addition_width;
		vars.offset = (vars.prev_x - (cube->screen_width / 2.0))
			* cube->shear_factor;
		while (vars.y < vars.max_new_y)
		{
			vars.prev_y = ((double)vars.y + cube->tilt_addition_height)
				+ vars.offset;
			if (vars.prev_y >= 0 && vars.prev_y < cube->screen_height)
				ft_tilt_3(cube, (vars.max_new_x * vars.y * 4) + (vars.x * 4),
					(cube->screen_width * (int)vars.prev_y * 4)
					+ ((int)vars.prev_x * 4));
			vars.y++;
		}
	}
}
