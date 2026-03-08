/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:33 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 17:36:20 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_game(t_cube *cube)
{
	struct timeval	tv;

	ft_mouvement(cube, 0.0f, 0.0f, tv);
	ft_draw_rays(cube);
	ft_floor_ceiling(cube);
	ft_draw_world(cube);
	ft_draw_enemies(cube);
	ft_draw_proj(cube);
	ft_weapon(cube);
	ft_heart(cube);
	ft_fov_mod(cube);
	if (cube->player.HP == 0)
		cube->state = DIED;
}

void	state_transition(t_cube *cube, t_state dest)
{
	if (dest == GAME)
	{
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_DISABLED);
		mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height
			/ 2);
		mlx_image_to_window(cube->mlx, cube->image, 0, 0);
		cube->prev_state = GAME;
	}
	else if (dest == DIED)
	{
		mlx_image_to_window(cube->mlx, cube->image_death, 0, 0);
		cube->prev_state = DIED;
	}
	else if (dest == MENU)
	{
		cube->prev_state = MENU;
		mlx_set_cursor_mode(cube->mlx, MLX_MOUSE_NORMAL);
	}
}

void	state_game(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < cube->screen_height * cube->screen_width * 4)
	{
		cube->lerp_buffer[i] = cube->prev_buffer[i];
		i++;
	}
	ft_game(cube);
	i = 0;
	while (i < cube->screen_height * cube->screen_width * 4)
	{
		cube->prev_buffer[i] = ft_lerp_pixels(cube->prev_buffer[i],
				cube->lerp_buffer[i], cube->heart.blur_lerp);
		i++;
	}
	ft_tilt(cube);
	ft_ups(cube, cube->image);
	draw_crosshair(cube);
	draw_grid(cube);
	draw_player(cube);
}

void	state_machine(t_cube *cube)
{
	int	i;

	i = 0;
	if (cube->state == MENU)
	{
		ft_menu(cube);
	}
	else if (cube->state == GAME)
		state_game(cube);
	else if (cube->state == DIED)
	{
		ft_died(cube, 0, 0);
		ft_ups(cube, cube->image_death);
	}
}
