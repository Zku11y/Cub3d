/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:27 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 01:05:25 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_fov_slider2(t_cube *cube, int *mouse_x, int *start_x)
{
	*start_x = *mouse_x - cube->menu.settings.fov.slider_start_x;
	if (*start_x > cube->menu.settings.fov.slider_end_x
		- cube->menu.settings.fov.slider_start_x)
		*start_x = cube->menu.settings.fov.slider_end_x
			- cube->menu.settings.fov.slider_start_x;
	else if (*start_x < 0)
		*start_x = 0;
	cube->init_fov = ((cube->menu.settings.fov.max_fov
				- cube->menu.settings.fov.min_fov) * ((double)*start_x
				/ (double)(cube->menu.settings.fov.slider_end_x
					- cube->menu.settings.fov.slider_start_x)))
		+ cube->menu.settings.fov.min_fov;
	cube->fov = cube->init_fov;
	cube->prev_fov = cube->init_fov;
	cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0)
			* RADIANT_RATE);
	cube->half_fov_rad = tan((cube->fov / 2.0) * RADIANT_RATE);
	cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
}

void	ft_fov_slider(t_cube *cube)
{
	int	mouse_x;
	int	mouse_y;
	int	start_x;

	start_x = (double)(cube->menu.settings.fov.slider_end_x
			- cube->menu.settings.fov.slider_start_x) * ((double)(cube->init_fov
				- cube->menu.settings.fov.min_fov)
			/ (double)(cube->menu.settings.fov.max_fov
				- cube->menu.settings.fov.min_fov));
	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	if (cube->menu.settings.mouse_held == FOV_SLIDER)
		ft_fov_slider2(cube, &mouse_x, &start_x);
	ft_renderer(cube, cube->menu.settings.fov.slider_1, start_x, 0);
}

void	ft_mouse_sens(t_cube *cube)
{
	double	start_x;

	int (mouse_x), (mouse_y);
	start_x = (double)(cube->menu.settings.mouse_sens.slider_end_x
			- cube->menu.settings.mouse_sens.slider_start_x)
		* (((cube->mouse_sens) - cube->menu.settings.mouse_sens.min_sens)
			/ (cube->menu.settings.mouse_sens.max_sens
				- cube->menu.settings.mouse_sens.min_sens));
	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	if (cube->menu.settings.mouse_held == MOUSE_SENS_SLIDER)
	{
		start_x = mouse_x - cube->menu.settings.mouse_sens.slider_start_x;
		if (start_x > cube->menu.settings.mouse_sens.slider_end_x
			- cube->menu.settings.mouse_sens.slider_start_x)
			start_x = cube->menu.settings.mouse_sens.slider_end_x
				- cube->menu.settings.mouse_sens.slider_start_x;
		else if (start_x < 0)
			start_x = 0;
		cube->mouse_sens = ((cube->menu.settings.mouse_sens.max_sens
					- cube->menu.settings.mouse_sens.min_sens) * (start_x
					/ (double)(cube->menu.settings.mouse_sens.slider_end_x
						- cube->menu.settings.mouse_sens.slider_start_x)))
			+ cube->menu.settings.mouse_sens.min_sens;
	}
	ft_renderer(cube, cube->menu.settings.mouse_sens.slider_2, start_x, 0);
}

void	ft_menu31(t_cube *cube, t_vars5 vars)
{
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& ((double)vars.mouse_x > ((double)cube->screen_width_buff * 0.92)
			&& (double)vars.mouse_x < ((double)cube->screen_width_buff * 0.97))
		&& ((double)vars.mouse_y > ((double)cube->screen_height_buff * 0.85))
		&& ((double)vars.mouse_y < (double)cube->screen_height_buff * 0.95))
		cube->menu.state = 1;
}
