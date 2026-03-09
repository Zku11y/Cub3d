/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:31 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 22:04:27 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_set_values(t_cube *cube, t_vars values)
{
	int	val;
	int	tex_val;

	val = (values.y * 4 * cube->screen_width) + (values.x * 4);
	tex_val = (int)(((int)values.j * cube->texture_died->bytes_per_pixel
				* cube->texture_died->width) + ((int)values.i
				* cube->texture_died->bytes_per_pixel));
	// return(printf("why dfk is PREV_BUFFER FREED???????\n") ,ft_clean(cube, cube->nu, 1));
	// printf("max : %d, val : %d, (%d, %d)\n", cube->screen_height * cube->screen_width * 4, val, values.x, values.y);
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
	printf("\e[31;1mOH HE FACKIN DAYD VRO \e[0m\n");
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
