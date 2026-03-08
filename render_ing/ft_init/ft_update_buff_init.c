/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_buff_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:43 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:12:44 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_update_buff_init_1(t_cube *cube)
{
	cube->menu.settings.res.start_y_1080_900 = 0.48 * cube->screen_height_buff;
	cube->menu.settings.res.end_y_1080_900 = 0.51 * cube->screen_height_buff;
	cube->menu.settings.res.start_y_480 = 0.59 * cube->screen_height_buff;
	cube->menu.settings.res.end_y_480 = 0.62 * cube->screen_height_buff;
	cube->menu.settings.crosshair.start_y = 0.178 * cube->screen_height_buff;
	cube->menu.settings.crosshair.end_y = 0.58 * cube->screen_height_buff;
	cube->crosshair_hori_start = (t_vect2){(cube->screen_width_buff / 2)
		- CROSSHAIR_LEN, (cube->screen_height_buff / 2) - CROSSHAIR_GIRTH, 0,
		0};
	cube->crosshair_hori_end = (t_vect2){(cube->screen_width_buff / 2)
		+ CROSSHAIR_LEN, (cube->screen_height_buff / 2) + CROSSHAIR_GIRTH, 0,
		0};
	cube->crosshair_vert_start = (t_vect2){(cube->screen_width_buff / 2)
		- CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) - CROSSHAIR_LEN, 0,
		0};
	cube->crosshair_vert_end = (t_vect2){(cube->screen_width_buff / 2)
		+ CROSSHAIR_GIRTH, (cube->screen_height_buff / 2) + CROSSHAIR_LEN, 0,
		0};
}

void	ft_update_buff_init_2(t_cube *cube)
{
	cube->menu.settings.ups.start_x15 = 0.089 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x15 = 0.11 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x26 = 0.162 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x26 = 0.183 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x37 = 0.235 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x37 = 0.256 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x48 = 0.310 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x48 = 0.331 * cube->screen_width_buff;
	cube->menu.settings.fov.slider_start_x = 0.065 * cube->screen_width_buff;
	cube->menu.settings.fov.slider_end_x = 0.354 * cube->screen_width_buff;
	cube->menu.settings.mouse_sens.slider_start_x = 0.605
		* cube->screen_width_buff;
	cube->menu.settings.mouse_sens.slider_end_x = 0.895
		* cube->screen_width_buff;
	cube->menu.settings.res.start_x_1080 = 0.055 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_1080 = 0.175 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_900 = 0.245 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_900 = 0.358 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_720 = 0.057 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_720 = 0.173 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_480 = 0.265 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_480 = 0.365 * cube->screen_width_buff;
	cube->menu.settings.crosshair.start_x = 0.636 * cube->screen_width_buff;
	cube->menu.settings.crosshair.end_x = 0.865 * cube->screen_width_buff;
	ft_updated_res_init(cube);
}

void	ft_updated_buff_init(t_cube *cube)
{
	mlx_resize_image(cube->image, cube->screen_width_buff,
		cube->screen_height_buff);
	mlx_resize_image(cube->image_death, cube->screen_width_buff,
		cube->screen_height_buff);
	mlx_set_window_size(cube->mlx, cube->screen_width_buff,
		cube->screen_height_buff);
	cube->mini_map_size = 0.2 * cube->screen_width_buff;
	cube->mini_map_grid_size = cube->mini_map_size / GRID_SIZE;
	cube->menu.settings.ups.start_y1234 = 0.78 * cube->screen_height_buff;
	cube->menu.settings.ups.end_y1234 = 0.807 * cube->screen_height_buff;
	cube->menu.settings.ups.start_y5678 = 0.873 * cube->screen_height_buff;
	cube->menu.settings.ups.end_y5678 = 0.9 * cube->screen_height_buff;
	cube->menu.settings.fov.slider_start_y = 0.20 * cube->screen_height_buff;
	cube->menu.settings.fov.slider_end_y = 0.24 * cube->screen_height_buff;
	cube->menu.settings.mouse_sens.slider_start_y = 0.78
		* cube->screen_height_buff;
	cube->menu.settings.mouse_sens.slider_end_y = 0.81
		* cube->screen_height_buff;
	ft_update_buff_init_1(cube);
	ft_update_buff_init_2(cube);
}
