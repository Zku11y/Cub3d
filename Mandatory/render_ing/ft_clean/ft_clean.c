/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 01:42:10 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 22:35:14 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_free_tex(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	ft_clean1(t_cube *cube)
{
	if (cube->mlx)
		mlx_close_window(cube->mlx);
	ft_free_tex(cube->menu.title);
	ft_free_tex(cube->menu.settings.background);
	ft_free_tex(cube->menu.settings.fov.bar_1);
	ft_free_tex(cube->menu.settings.bar_2);
	ft_free_tex(cube->menu.settings.fov.slider_1);
	ft_free_tex(cube->menu.settings.slider_2);
	ft_free_tex(cube->menu.settings.ups.x1_glow);
	ft_free_tex(cube->menu.settings.ups.x2_glow);
	ft_free_tex(cube->menu.settings.ups.x3_glow);
	ft_free_tex(cube->menu.settings.ups.x4_glow);
	ft_free_tex(cube->menu.settings.ups.x5_glow);
	ft_free_tex(cube->menu.settings.ups.x6_glow);
	ft_free_tex(cube->menu.settings.ups.x7_glow);
	ft_free_tex(cube->menu.settings.ups.x8_glow);
	ft_free_tex(cube->menu.settings.mouse_sens.slider_2);
	ft_free_tex(cube->menu.settings.res._480);
	ft_free_tex(cube->menu.settings.res._720);
	ft_free_tex(cube->menu.settings.res._900);
	ft_free_tex(cube->menu.settings.res._1080);
	ft_free_tex(cube->menu.settings.crosshair.border);
	ft_free_tex(cube->player.weapon.idle_texture);
	ft_free_tex(cube->player.weapon.shoot_texture);
	ft_free_tex(cube->player.weapon.pump_texture);
}

void	ft_clean2(t_cube *cube)
{
	ft_free_tex(cube->heart.frame_1);
	ft_free_tex(cube->heart.frame_2);
	ft_free_tex(cube->heart.frame_3);
	ft_free_tex(cube->heart.frame_4);
	if (cube->blood.frame)
	{
		ft_free_tex(cube->blood.frame[0]);
		ft_free_tex(cube->blood.frame[1]);
		ft_free_tex(cube->blood.frame[2]);
		ft_free_tex(cube->blood.frame[3]);
		ft_free_tex(cube->blood.frame[4]);
		ft_free_tex(cube->blood.frame[5]);
		ft_free_tex(cube->blood.frame[6]);
		ft_free_tex(cube->blood.frame[7]);
		ft_free_tex(cube->blood.frame[8]);
		ft_free_tex(cube->blood.frame[9]);
		ft_free_tex(cube->blood.frame[10]);
		ft_free_tex(cube->blood.frame[11]);
		free(cube->blood.frame);
	}
	ft_free_tex(cube->texture_died);
	ft_free_tex(cube->crosshair);
	if (cube->lerp_buffer)
		free(cube->lerp_buffer);
}

void	ft_clean(t_cube *cube, t_nc *nu, int flag)
{
	ft_clean1(cube);
	ft_clean2(cube);
	if (cube->z_buffer)
		free(cube->z_buffer);
	if (cube->rays)
		free(cube->rays);
	if (cube->enemy)
		free(cube->enemy);
	if (cube->projectiles)
		free(cube->projectiles);
	if (cube->prev_buffer)
		free(cube->prev_buffer);
	if (cube->new_buffer)
		free(cube->new_buffer);
	if (cube->image)
		mlx_delete_image(cube->mlx, cube->image);
	if (cube->image_death)
		mlx_delete_image(cube->mlx, cube->image_death);
	if (cube->mlx)
		mlx_terminate(cube->mlx);
	free_nu(nu);
	free(cube);
	if (flag == 1)
		perror("Error\n");
	exit(flag);
}
