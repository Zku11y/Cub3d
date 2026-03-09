/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:58 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 22:30:23 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_enemy6(t_cube *cube, mlx_texture_t *texture,
		t_vars10 *vars)
{
	if (vars->y < 0)
		vars->y = 0;
	if (!check_screen_limits(cube, (t_vect2){vars->start_x, vars->start_y, 0,
			0}))
	{
		vars->k = (vars->x * texture->bytes_per_pixel) + (texture->width
				* texture->bytes_per_pixel * vars->y);
		if (texture->pixels[vars->k + 3] > 128)
		{
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 0] = (texture->pixels[vars->k + 0]
				* vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 1] = (texture->pixels[vars->k + 1]
				* vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 2] = (texture->pixels[vars->k + 2]
				* vars->tmp) + (0x33 * (1.0 - vars->tmp));
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 3] = texture->pixels[vars->k + 3];
		}
	}
	vars->start_y++;
}

void	ft_enemy7(t_cube *cube, mlx_texture_t *texture,
		t_vars10 *vars)
{
	while (vars->start_x < vars->end_x)
	{
		vars->start_y = vars->const_y;
		vars->x = (int)vars->tex_x;
		if (vars->x >= (int)texture->width)
			vars->x = texture->width - 1;
		if (vars->x < 0)
			vars->x = 0;
		vars->tex_y = 0;
		if (cube->z_buffer[vars->start_x] > vars->dst)
		{
			cube->z_buffer[vars->start_x] = vars->dst;
			while (vars->start_y < vars->end_y)
			{
				vars->y = (int)vars->tex_y;
				if (vars->y >= (int)texture->height)
					vars->y = texture->height - 1;
				ft_enemy6(cube, texture, vars);
				vars->tex_y += vars->scale_ratio;
			}
		}
		vars->tex_x += vars->scale_ratio;
		vars->start_x++;
	}
}

void	ft_init_projectile(t_cube *cube, t_enemy *enemy, t_vect2 *dir)
{
	t_projectile	proj;
	int				i;

	proj.x = enemy->x;
	proj.y = enemy->y;
	proj.dir = *dir;
	proj.in_use = 1;
	proj.DMG = enemy->DMG;
	proj.texture = cube->texture6;
	proj.dst_traveled = 0;
	proj.speed = 7;
	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (cube->projectiles[i].in_use == 0)
		{
			cube->projectiles[i] = proj;
			break ;
		}
		i++;
	}
}

void	ft_projectile(t_cube *cube, t_projectile *projectile)
{
	t_vars10	vars;

	if (!ft_projectile2(cube, projectile, &vars) || !ft_projectile3(cube,
			projectile, &vars) || !ft_projectile4(cube, projectile, &vars))
		return ;
	if (vars.start_y >= cube->screen_height)
		return ;
	if (vars.end_x > cube->screen_width)
		vars.end_x = cube->screen_width;
	if (vars.end_y > cube->screen_height)
		vars.end_y = cube->screen_height;
	ft_projectile6(cube, projectile, &vars);
}
