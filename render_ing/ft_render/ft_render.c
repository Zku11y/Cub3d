/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:12 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:14:13 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_renderer2(t_cube *cube, t_vars7 *vars, int start_x, int start_y)
{
	while (++vars->x < cube->screen_width_buff)
	{
		vars->tex_x = (double)(vars->x) * ((double)(vars->texture->width)
				/ (double)(cube->screen_width_buff));
		vars->pixel_cords = ((vars->y + start_y) * 4 * cube->screen_width_buff)
			+ ((vars->x + start_x) * 4);
		vars->title_cords = (vars->tex_y * 4 * vars->texture->width)
			+ (vars->tex_x * 4);
		if (vars->tex_x >= vars->texture->width
			|| vars->tex_y >= vars->texture->height
			|| vars->texture->pixels[vars->tex_y * 4 * vars->texture->width
				+ vars->tex_x * 4 + 3] < 127)
			continue ;
		cube->image->pixels[vars->pixel_cords
			+ 0] = vars->texture->pixels[vars->title_cords + 0];
		cube->image->pixels[vars->pixel_cords
			+ 1] = vars->texture->pixels[vars->title_cords + 1];
		cube->image->pixels[vars->pixel_cords
			+ 2] = vars->texture->pixels[vars->title_cords + 2];
		cube->image->pixels[vars->pixel_cords
			+ 3] = vars->texture->pixels[vars->title_cords + 3];
	}
}

void	ft_renderer(t_cube *cube, mlx_texture_t *texture, int start_x,
		int start_y)
{
	t_vars7	vars;

	vars.x = 1;
	vars.y = 0;
	vars.texture = texture;
	while (vars.y < cube->screen_height_buff)
	{
		vars.x = 0;
		vars.tex_y = (double)(vars.y) *((double)(texture->height)
				/ (double)(cube->screen_height_buff));
		ft_renderer2(cube, &vars, start_x, start_y);
		vars.y++;
	}
}

void	ft_prev_renderer2(t_cube *cube, t_vars7 *vars, int start_x, int start_y)
{
	while (++vars->x < cube->screen_width)
	{
		vars->tex_x = (double)(vars->x) * ((double)(vars->texture->width)
				/ (double)(cube->screen_width));
		vars->pixel_cords = ((vars->y + start_y) * 4 * cube->screen_width)
			+ ((vars->x + start_x) * 4);
		vars->title_cords = (vars->tex_y * 4 * vars->texture->width)
			+ (vars->tex_x * 4);
		if (vars->tex_x >= vars->texture->width
			|| vars->tex_y >= vars->texture->height
			|| vars->texture->pixels[vars->tex_y * 4 * vars->texture->width
				+ vars->tex_x * 4 + 3] < 50)
			continue ;
		cube->prev_buffer[vars->pixel_cords
			+ 0] = vars->texture->pixels[vars->title_cords + 0];
		cube->prev_buffer[vars->pixel_cords
			+ 1] = vars->texture->pixels[vars->title_cords + 1];
		cube->prev_buffer[vars->pixel_cords
			+ 2] = vars->texture->pixels[vars->title_cords + 2];
		cube->prev_buffer[vars->pixel_cords
			+ 3] = vars->texture->pixels[vars->title_cords + 3];
	}
}

void	ft_prev_renderer(t_cube *cube, mlx_texture_t *texture, int start_x,
		int start_y)
{
	t_vars7	vars;

	vars.x = -1;
	vars.y = 0;
	vars.texture = texture;
	while (vars.y < cube->screen_height)
	{
		vars.x = -1;
		vars.tex_y = (double)(vars.y) *((double)(texture->height)
				/ (double)(cube->screen_height));
		ft_prev_renderer2(cube, &vars, start_x, start_y);
		vars.y++;
	}
}
