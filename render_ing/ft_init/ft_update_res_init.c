/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_res_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:45 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 19:13:28 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool ft_updated_res_realloc(t_cube *cube){
	free(cube->prev_buffer);
	free(cube->new_buffer);
	free(cube->lerp_buffer);
	free(cube->z_buffer);
	free(cube->rays);
	cube->prev_buffer = NULL;
	cube->new_buffer = NULL;
	cube->lerp_buffer = NULL;
	cube->z_buffer = NULL;
	cube->rays = NULL;
	cube->prev_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	cube->new_buffer = ts_calloc((cube->screen_height
				- cube->tilt_addition_height) * (cube->screen_width
				- cube->tilt_addition_width), 4);
	cube->lerp_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	cube->rays = ts_calloc(cube->res + 1, sizeof(t_ray));
	cube->z_buffer = ts_calloc(cube->screen_width + 1, sizeof(double));
	if(!(cube->prev_buffer) || !(cube->new_buffer) || !(cube->lerp_buffer) || !(cube->rays) || !(cube->z_buffer))
		return (ft_clean(cube), false);	
	return true;
}

void	ft_updated_res_init(t_cube *cube)
{
	cube->res = cube->screen_width;
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
	cube->move_increase = 0.05 * cube->screen_height;
	cube->pitch_max = cube->screen_height + 100;
	if(!ft_updated_res_realloc(cube))
		return (ft_clean(cube));
	cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0)
			* RADIANT_RATE);
	cube->line_girth = (int)(cube->screen_width / cube->res);
	cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
	clear_image(cube);
}
