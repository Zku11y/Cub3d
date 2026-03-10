/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:33 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 15:22:00 by skully           ###   ########.fr       */
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
	if (cube->player.HP == 0)
		return (cube->state = DIED, (void)(cube->trans_dst = 0));
}

void	draw_transition(t_cube *cube)
{
	int	x;
	int	y;
	int	max_x;

	x = 0;
	max_x = (cube->screen_width_buff / 2) - cube->transition;
	if (max_x <= 0)
		return ;
	while (x < max_x)
	{
		y = 0;
		while (y < cube->screen_height_buff)
		{
			mlx_put_pixel(cube->image, x, y, 0x000000ff);
			y++;
		}
		x++;
	}
}

void	draw_transition2(t_cube *cube)
{
	int	x;
	int	y;
	int	min_x;

	min_x = (cube->screen_width_buff / 2) + cube->transition;
	if (min_x >= cube->screen_width_buff)
		return ;
	x = min_x;
	while (x < cube->screen_width_buff)
	{
		y = 0;
		while (y < cube->screen_height_buff)
		{
			mlx_put_pixel(cube->image, x, y, 0x000000ff);
			y++;
		}
		x++;
	}
}

void	state_machine(t_cube *cube)
{
	int	i;

	i = 0;
	cube->transition = ft_lerp_move(cube->trans_dst, cube->transition, 0.9);
	if (cube->prev_state == MENU)
	{
		ft_menu(cube);
	}
	else if (cube->prev_state == GAME)
		state_game(cube);
	else if (cube->prev_state == DIED)
	{
		ft_died(cube, 0, 0);
		ft_ups(cube, cube->image_death);
	}
	draw_transition(cube);
	draw_transition2(cube);
}
