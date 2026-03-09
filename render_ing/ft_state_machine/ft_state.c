/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:33 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 22:16:50 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void ft_init_map(t_cube *cube)
{
	if(cube->nu->next == NULL)
		return(ft_clean(cube, cube->nu, 0));
	cube->nu = cube->nu->next;
	cube->map = cube->nu->map;
	cube->player.x = (GRID_SIZE * (double)cube->nu->start->x) + GRID_SIZE / 2.0;
	cube->player.y = (GRID_SIZE * (double)cube->nu->start->y) + GRID_SIZE / 2.0;
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);	
	// printf("player : (%lf, %lf)\n", cube->player.x, cube->player.y);
	cube->map_x = cube->nu->x;
	cube->map_y = cube->nu->y;
	int y = 0;
	int x = 0;

	while(y < cube->nu->y){
		x = 0;
		while(x < cube->nu->x){
			if(cube->nu->map[y][x] == '1')
				printf("\e[1;31m1\e[0m");
			else
				printf("\e[1;32m%c\e[0m", cube->nu->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	if (cube->nu->start->door == 'E')
		cube->player.angle = 0;
	else if (cube->nu->start->door == 'W')
		cube->player.angle = PI;
	else if (cube->nu->start->door == 'S')
		cube->player.angle = PI / 2.0;
	else if (cube->nu->start->door == 'N')
		cube->player.angle = (PI / 2.0) + PI;
	cube->player.HP = MAX_HP;
	cube->player.delay = false;
	ft_init_enemies(cube);
}

void	ft_game(t_cube *cube)
{
	if(cube->player.x > (cube->nu->end->x * GRID_SIZE) && cube->player.x < ((cube->nu->end->x * GRID_SIZE) + GRID_SIZE) && cube->player.y > (cube->nu->end->y * GRID_SIZE) && cube->player.y < ((cube->nu->end->y * GRID_SIZE) + GRID_SIZE)){
		ft_init_map(cube);
	}
	ft_mouvement(cube, 0.0f, 0.0f, (struct timeval){0, 0});
	ft_draw_rays(cube);
	ft_floor_ceiling(cube);
	ft_draw_world(cube);
	ft_draw_enemies(cube);
	ft_draw_proj(cube);
	ft_weapon(cube);
	ft_heart(cube);
	ft_fov_mod(cube);
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
	if (cube->player.HP == 0){
		cube->state = DIED;
		cube->trans_dst = 0;
	}
}

void draw_transition(t_cube *cube)
{
	int x;	
	int y;	
	int max_x;

	x = 0;
	max_x = (cube->screen_width_buff / 2) - cube->transition;
	if(max_x <= 0)
		return;
	while(x < max_x)
	{
		y = 0;	
		while(y < cube->screen_height_buff)
		{
			mlx_put_pixel(cube->image, x, y, 0x000000ff);
			y++;
		}
		x++;
	}
}

void draw_transition2(t_cube *cube)
{
	int x;	
	int y;	
	int min_x;

	min_x = (cube->screen_width_buff / 2) + cube->transition;
	if(min_x >= cube->screen_width_buff)
		return;
	x = min_x;
	while(x < cube->screen_width_buff)
	{
		y = 0;	
		while(y < cube->screen_height_buff)
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
