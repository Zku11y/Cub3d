/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:33 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 20:30:41 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	// int	i;
	// i = 0;
	// while (i < cube->screen_height * cube->screen_width * 4)
	// {
	// 	cube->lerp_buffer[i] = cube->prev_buffer[i];
	// 	i++;
	// }
	// i = 0;
	// while (i < cube->screen_height * cube->screen_width * 4)
	// {
	// 	cube->prev_buffer[i] = ft_lerp_pixels(cube->prev_buffer[i],
	// 			cube->lerp_buffer[i], cube->heart.blur_lerp);
	// 	i++;
	// }
	// printf("before\n");
	// printf("after\n");
	ft_game(cube);
	// draw_crosshair(cube);
	// draw_grid(cube);
	// draw_player(cube);
	ft_tilt(cube);
	// ft_ups(cube, cube->image);
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
