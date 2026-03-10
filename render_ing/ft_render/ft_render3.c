/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:17 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 20:28:41 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_draw_texture2(t_cube *cube, t_ray *ray, t_vars11 *vars)
{
	while (vars->start.y < cube->screen_height && vars->start.y < vars->end.y
		&& vars->cords.y < ray->texture->height)
	{
		if (!check_screen_limits(cube, vars->start))
		{
			vars->k = ((int)vars->cords.x * ray->texture->bytes_per_pixel)
				+ (ray->texture->width * ray->texture->bytes_per_pixel
					* (int)vars->cords.y);
			cube->image->pixels[(cube->screen_width * (int)vars->start.y * 4)
				+ ((int)vars->start.x * 4) + 0] = ray->texture->pixels[vars->k
				+ 0];
			cube->image->pixels[(cube->screen_width * (int)vars->start.y * 4)
				+ ((int)vars->start.x * 4) + 1] = ray->texture->pixels[vars->k
				+ 1];
			cube->image->pixels[(cube->screen_width * (int)vars->start.y * 4)
				+ ((int)vars->start.x * 4) + 2] = ray->texture->pixels[vars->k
				+ 2];
			cube->image->pixels[(cube->screen_width * (int)vars->start.y * 4)
				+ ((int)vars->start.x * 4) + 3] = ray->texture->pixels[vars->k
				+ 3];
		}
		vars->cords.y += vars->ratio.y;
		vars->start.y++;
	}
}

void	ft_draw_texture1(t_cube *cube, t_ray *ray, t_vars11 *vars)
{
	vars->cords.x = ray->texture->width * ray->normal_dst;
	if (vars->cords.x < 0)
		vars->cords.x = 0;
	if (vars->cords.x >= ray->texture->width)
		vars->cords.x = ray->texture->width - 1;
}

void	ft_draw_texture(t_cube *cube, t_ray *ray, t_vect2 start, t_vect2 end)
{
	t_vars11	vars;

	vars.start = start;
	vars.end = end;
	vars.len = ((GRID_SIZE) / (ray->length * cos(ray->real_angle
					- cube->player.angle))) * cube->proj_dst;
	if (ray->texture == NULL)
		return ;
	vars.cords.y = 0;
	vars.ratio.y = ray->texture->height / vars.len;
	if (check_screen_limits(cube, vars.start) && vars.start.y <= 0)
	{
		vars.cords.y = vars.ratio.y * ((-1) * vars.start.y);
		vars.start.y = 0;
	}
	ft_draw_texture1(cube, ray, &vars);
	ft_draw_texture2(cube, ray, &vars);
}

void	ft_ray_init(t_cube *cube, t_ray *ray, double angle)
{
	t_vect2	hori;
	t_vect2	vert;

	ray->start.x = cube->player.x;
	ray->start.y = cube->player.y;
	ray->angle = angle;
	if (ray->angle >= PI && ray->angle <= 2 * PI)
		ray->y_dir = UP;
	else
		ray->y_dir = DOWN;
	if ((ray->angle >= 0.5 * PI) && (ray->angle <= 1.5 * PI))
		ray->x_dir = LEFT;
	else
		ray->x_dir = RIGHT;
	if (ray->y_dir == UP && ray->x_dir == RIGHT)
		ray->angle = (2 * PI) - angle;
	else if (ray->y_dir == UP && ray->x_dir == LEFT)
		ray->angle = angle - PI;
	else if (ray->y_dir == DOWN && ray->x_dir == LEFT)
		ray->angle = PI - angle;

		hori = hori_first_point(cube, ray);
	vert = vert_first_point(cube, ray);
	ray->end = calc_length(cube, hori, vert, ray);
}
