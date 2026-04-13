/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:31 by mdakni            #+#    #+#             */
/*   Updated: 2026/04/10 13:54:52 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_map1(t_cube *cube)
{
	int (x), (y);
	y = 0;
	x = 0;
	while (y < cube->nu->y)
	{
		x = 0;
		while (x < cube->nu->x)
		{
			if (cube->nu->map[y][x] == '1')
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
}

void	ft_init_map(t_cube *cube)
{
	if (cube->nu->next == NULL)
		return (ft_clean(cube, cube->nu, 0));
	cube->nu = cube->nu->next;
	cube->map = cube->nu->map;
	cube->player.x = (GRID_SIZE * (double)cube->nu->start->x) + GRID_SIZE / 2.0;
	cube->player.y = (GRID_SIZE * (double)cube->nu->start->y) + GRID_SIZE / 2.0;
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
	cube->map_x = cube->nu->x;
	cube->map_y = cube->nu->y;
	ft_init_map1(cube);
	cube->player.hp = MAX_HP;
	cube->player.delay = false;
	ft_init_enemies(cube);
}

void	ft_game(t_cube *cube)
{
	if (cube->player.x > (cube->nu->end->x * GRID_SIZE)
		&& cube->player.x < ((cube->nu->end->x * GRID_SIZE) + GRID_SIZE)
		&& cube->player.y > (cube->nu->end->y * GRID_SIZE)
		&& cube->player.y < ((cube->nu->end->y * GRID_SIZE) + GRID_SIZE))
	{
		ft_init_map(cube);
	}
	ft_mouvement(cube, 0.0f, 0.0f, (struct timeval){0, 0});
	ft_draw_rays(cube); // negligable
	ft_floor_ceiling(cube); // ~20fps
	ft_draw_world(cube); // negligable
	ft_draw_enemies(cube); // negligable
	ft_draw_proj(cube); // negligable
	ft_weapon(cube); // negligable
	ft_heart(cube); // negligable
	ft_fov_mod(cube); // negligable
}

void	ft_set_values(t_cube *cube, t_vars values)
{
	int	val;
	int	tex_val;

	val = (values.y * 4 * cube->screen_width) + (values.x * 4);
	tex_val = (int)(((int)values.j * cube->texture_died->bytes_per_pixel
				* cube->texture_died->width) + ((int)values.i
				* cube->texture_died->bytes_per_pixel));
	cube->prev_buffer[val] = cube->texture_died->pixels[tex_val + 0];
	cube->prev_buffer[val + 1] = cube->texture_died->pixels[tex_val + 1];
	cube->prev_buffer[val + 2] = cube->texture_died->pixels[tex_val + 2];
	cube->prev_buffer[val + 3] = cube->texture_died->pixels[tex_val + 3];
}

void	ft_died(t_cube *cube, double i, double j)
{
	double	i_iter;
	double	j_iter;

	int (x), (y);
	x = 0;
	y = 0;
	i_iter = (double)cube->texture_died->width / (double)cube->screen_width;
	j_iter = (double)cube->texture_died->height / (double)cube->screen_height;
	while (x < cube->screen_width)
	{
		y = 0;
		j = 0;
		while (y < cube->screen_height)
		{
			if ((int)i >= (int)cube->texture_died->width)
				i = cube->texture_died->width - 1;
			if ((int)j >= (int)cube->texture_died->height)
				j = cube->texture_died->height - 1;
			ft_set_values(cube, (t_vars){x, y, i, j});
			y++;
			j += j_iter;
		}
		i += i_iter;
		x++;
	}
}
