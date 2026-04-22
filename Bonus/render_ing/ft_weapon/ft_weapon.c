/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_weapon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:15:10 by mdakni            #+#    #+#             */
/*   Updated: 2026/04/22 12:36:36 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_weapon_1(t_cube *cube, long current_time)
{
	if (cube->player.attacked == true)
	{
		cube->player.weapon.pitch_changed = true;
		cube->player.weapon.pitch_back = false;
		cube->player.weapon.pitch_og = cube->pitch;
		cube->player.weapon.pitch_dst = cube->pitch
			+ cube->player.weapon.pitch_increase;
		cube->player.weapon.texture = cube->player.weapon.shoot_texture;
		cube->player.weapon.frame_delay = current_time;
		cube->player.weapon.delay = true;
		cube->player.attacked = false;
	}
}

void	ft_weapon_2(t_cube *cube)
{
	if (!cube->player.weapon.pitch_back)
	{
		cube->pitch += cube->player.weapon.pitch_increase * 4.0;
		cube->player.weapon.pitch_increased
			+= cube->player.weapon.pitch_increase * 4.0;
		if (cube->player.weapon.pitch_increased >= MAX_RECOIL)
		{
			cube->player.weapon.pitch_increased = 0;
			cube->player.weapon.pitch_dst = cube->player.weapon.pitch_og;
			cube->player.weapon.pitch_back = true;
		}
	}
	if (cube->player.weapon.pitch_back)
	{
		cube->pitch -= cube->player.weapon.pitch_increase;
		cube->player.weapon.pitch_increased
			+= cube->player.weapon.pitch_increase;
		if (cube->player.weapon.pitch_increased >= MAX_RECOIL)
		{
			cube->player.weapon.pitch_increased = 0;
			cube->player.weapon.pitch_changed = false;
		}
	}
}

void	ft_weapon_3(t_cube *cube, t_vars3 *vars)
{
	vars->tex_x = (double)(vars->x - vars->start_x)
		* ((double)(cube->player.weapon.texture->width)
			/ (double)(cube->screen_width - vars->start_x));
	vars->prev_cords = ((int)(vars->y) * 4 * cube->screen_width) + ((int)vars->x
			* 4);
	vars->weapon_cords = vars->tex_y * 4 * cube->player.weapon.texture->width
		+ vars->tex_x * 4;
	if (vars->tex_x >= (int)cube->player.weapon.texture->width
		|| vars->tex_y >= (int)cube->player.weapon.texture->height
		|| cube->player.weapon.texture->pixels[vars->weapon_cords + 3] == 0)
		return ((void)vars->x++);
	cube->prev_buffer[vars->prev_cords
		+ 0] = cube->player.weapon.texture->pixels[vars->weapon_cords + 0];
	cube->prev_buffer[vars->prev_cords
		+ 1] = cube->player.weapon.texture->pixels[vars->weapon_cords + 1];
	cube->prev_buffer[vars->prev_cords
		+ 2] = cube->player.weapon.texture->pixels[vars->weapon_cords + 2];
	cube->prev_buffer[vars->prev_cords
		+ 3] = cube->player.weapon.texture->pixels[vars->weapon_cords + 3];
	(vars->x)++;
}

void	ft_weapon_4(t_cube *cube, long current_time)
{
	int	time;

	time = (int)(current_time - cube->player.weapon.frame_delay);
	if (cube->player.delay == true)
	{
		if (time >= 150 && time <= 500)
			cube->player.weapon.texture = cube->player.weapon.idle_texture;
		else if (time > 500 && time <= 800)
			cube->player.weapon.texture = cube->player.weapon.pump_texture;
		else if (time > 800 && time <= 900)
		{
			cube->player.weapon.texture = cube->player.weapon.idle_texture;
			cube->player.delay = false;
		}
	}
}

void	ft_weapon(t_cube *cube)
{
	struct timeval	tv;
	t_vars3			vars;

	vars.start_x = cube->screen_width * 0.1;
	vars.start_y = (cube->screen_height * 0.1);
	vars.x = vars.start_x;
	vars.y = vars.start_y;
	gettimeofday(&tv, NULL);
	vars.current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if(cube->player.delay == false && vars.current_time - cube->player.weapon.idle_time > 250){
		mlx_texture_t *tmp = cube->player.weapon.idle_texture;
		cube->player.weapon.idle_texture = cube->player.weapon.idle_texture_2;
		cube->player.weapon.idle_texture_2 = tmp;
		cube->player.weapon.idle_time = vars.current_time;
		cube->player.weapon.texture = cube->player.weapon.idle_texture;
	}
	ft_weapon_1(cube, vars.current_time);
	if (cube->player.weapon.pitch_changed)
		ft_weapon_2(cube);
	while (vars.y < cube->screen_height)
	{
		vars.x = vars.start_x;
		vars.tex_y = (double)(vars.y - vars.start_y)
			*((double)(cube->player.weapon.texture->height)
				/ (double)((cube->screen_height
						+ cube->player.weapon.move_lerp)));
		while (vars.x < cube->screen_width)
			ft_weapon_3(cube, &vars);
		vars.y++;
	}
	ft_weapon_4(cube, vars.current_time);
}
