/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:49 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 03:01:09 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_image(t_cube *cube)
{
	int	buffer_size;

	buffer_size = cube->screen_height * cube->screen_width * 4;
	ts_memset(cube->image->pixels, 0, buffer_size);
}

unsigned long	ft_rand(unsigned long *seed)
{
	*seed = (*seed * 1103515245 + 12345) & 0x7fffffff;
	return (*seed);
}

void	ft_rectangle_prev(t_cube *cube, t_vect2 start_cords, t_vect2 end_cords,
		t_colour color)
{
	int (start_x), (start_y), (end_x), (end_y);
	start_y = (int)(start_cords.y);
	end_x = (int)(end_cords.x);
	end_y = (int)(end_cords.y);
	while (start_y < end_y)
	{
		start_x = (int)(start_cords.x);
		while (start_x < end_x)
		{
			cube->image->pixels[(start_y * cube->screen_width * 4) + (start_x
					* 4) + 0] = color.r;
			cube->image->pixels[(start_y * cube->screen_width * 4) + (start_x
					* 4) + 1] = color.g;
			cube->image->pixels[(start_y * cube->screen_width * 4) + (start_x
					* 4) + 2] = color.b;
			cube->image->pixels[(start_y * cube->screen_width * 4) + (start_x
					* 4) + 3] = 255;
			start_x++;
		}
		start_y++;
	}
}

void	ft_load_png(t_cube *cube, mlx_texture_t **tex_buff, char *path)
{
	if (!path || !tex_buff)
		ft_clean(cube, cube->nu, 1);
	*tex_buff = mlx_load_png(path);
}

void	calc_length1(t_cube *cube, double len_vert, t_vect2 vert, t_ray *ray)
{
	ray->length = len_vert;
	if (ray->x_dir == RIGHT)
	{
		ray->texture = cube->nu->txtrs[2];
		ray->normal_dst = fmod(vert.y, GRID_SIZE) / GRID_SIZE;
	}
	else
	{
		ray->texture = cube->nu->txtrs[3];
		ray->normal_dst = 1 - (fmod(vert.y, GRID_SIZE) / GRID_SIZE);
	}
}
