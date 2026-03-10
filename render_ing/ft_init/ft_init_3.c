/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:37 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 00:58:26 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_91(t_cube *cube, t_nc *nu, struct timeval tv)
{
	cube->lerp_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	if (!(cube->lerp_buffer))
		return (ft_clean(cube, cube->nu, 1));
	cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
	cube->fps = 0;
	cube->grain = true;
	cube->pitch = 0.0;
	cube->z_buffer = ts_calloc(cube->screen_width, sizeof(double));
	if (!(cube->z_buffer))
		return (ft_clean(cube, cube->nu, 1));
	cube->rays = ts_calloc(cube->res + 1, sizeof(t_ray));
	if (!(cube->rays))
		return (ft_clean(cube, cube->nu, 1));
	cube->init_t = tv.tv_sec;
	cube->final_t = tv.tv_sec;
	cube->moving = false;
	cube->enemy = ts_calloc(ENEMY_NUM + 1, sizeof(t_enemy));
	if (!(cube->enemy))
		return (ft_clean(cube, cube->nu, 1));
	ft_init_enemies(cube);
	cube->player.grid_x = (int)(cube->player.x / GRID_SIZE);
	cube->player.grid_y = (int)(cube->player.y / GRID_SIZE);
}

void	ft_init_9(t_cube *cube, t_nc *nu)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
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
	cube->projectiles = ts_calloc(MAX_PROJECTILES + 1, sizeof(t_projectile));
	cube->prev_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	cube->new_buffer = ts_calloc((cube->screen_height
				- cube->tilt_addition_height) * (cube->screen_width
				- cube->tilt_addition_width), 4);
	if (!(cube->projectiles) || !(cube->prev_buffer) || !(cube->new_buffer))
		return (ft_clean(cube, cube->nu, 1));
	ft_init_91(cube, nu, tv);
}
