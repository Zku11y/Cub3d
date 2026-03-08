/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:49 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 21:57:19 by mdakni           ###   ########.fr       */
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

void	ft_rectangle(t_cube *cube, t_vect2 start_cords, t_vect2 end_cords,
		int color)
{
	uint32_t	*prev;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;

	prev = (uint32_t *)cube->image->pixels;
	start_x = (int)(start_cords.x);
	start_y = (int)(start_cords.y);
	end_x = (int)(end_cords.x);
	end_y = (int)(end_cords.y);
	while (start_y < end_y)
	{
		start_x = (int)(start_cords.x);
		while (start_x < end_x)
		{
			prev[(start_y * cube->screen_width_buff) + (start_x)] = color;
			start_x++;
		}
		start_y++;
	}
}
void ft_load_png(t_cube *cube, mlx_texture_t **tex_buff, char *path){
	if(!path || !tex_buff)
		ft_clean(cube, cube->nu, 1);
	*tex_buff = mlx_load_png(path);
}
