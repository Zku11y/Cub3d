/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:14:48 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 23:39:19 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_screen_limits(t_cube *cube, t_vect2 len)
{
	if (len.x >= cube->screen_width)
		return (true);
	else if (len.x < 0)
		return (true);
	if (len.y >= cube->screen_height)
		return (true);
	else if (len.y < 0)
		return (true);
	return (false);
}

t_vect2	calc_length(t_cube *cube, t_vect2 hori, t_vect2 vert, t_ray *ray)
{
	double	len_hori;
	double	len_vert;

	len_hori = (fabs(hori.y - cube->player.y) / sin(ray->angle));
	len_vert = (fabs(vert.x - cube->player.x) / cos(ray->angle));
	if (len_hori < len_vert)
	{
		ray->length = len_hori;
        
        if (ray->hori_obstacle == 'H')
            ray->texture = cube->nu->txtrs[ED];
        else if (ray->y_dir == UP)
            ray->texture = cube->nu->txtrs[WA];
        else
            ray->texture = cube->nu->txtrs[WA];          

        if (ray->y_dir == UP)
            ray->normal_dst = fmod(hori.x, GRID_SIZE) / GRID_SIZE;
        else
            ray->normal_dst = 1 - (fmod(hori.x, GRID_SIZE) / GRID_SIZE);
            
        return (hori);
	}
	ray->length = len_vert;
	if (ray->vert_obstacle == 'V')
        ray->texture = cube->nu->txtrs[ED];
    else if (ray->x_dir == RIGHT)
        ray->texture = cube->nu->txtrs[WA];
    else
        ray->texture = cube->nu->txtrs[WA];
        
    if (ray->x_dir == RIGHT)
        ray->normal_dst = fmod(vert.y, GRID_SIZE) / GRID_SIZE;
    else
        ray->normal_dst = 1 - (fmod(vert.y, GRID_SIZE) / GRID_SIZE);

	return (vert);
}

void	set_screen_buff_limits(t_cube *cube, t_vect2 *len)
{
	if (len->x > cube->screen_width_buff)
		len->x = cube->screen_width_buff - 1;
	else if (len->x < 0)
		len->x = 0;
	if (len->y > cube->screen_height_buff)
		len->y = cube->screen_height_buff - 1;
	else if (len->y < 0)
		len->y = 0;
}

void	ft_draw_line(t_cube *cube, t_vect2 start, t_vect2 finish, int color)
{
	t_vect2	add;
	t_vect2	mod;

	set_screen_buff_limits(cube, &start);
	set_screen_buff_limits(cube, &finish);
	mod.x = finish.x - start.x;
	mod.y = finish.y - start.y;
	if (fabs(mod.x) >= fabs(mod.y))
	{
		add.x = mod.x / fabs(mod.x);
		add.y = mod.y / fabs(mod.x);
	}
	else
	{
		add.x = mod.x / fabs(mod.y);
		add.y = mod.y / fabs(mod.y);
	}
	while (fabs(start.x - finish.x) > 0.5 || fabs(start.y - finish.y) > 0.5)
	{
		mlx_put_pixel(cube->image, (int)round(start.x), (int)round(start.y),
			color);
		start.x += add.x;
		start.y += add.y;
	}
}

void	ft_angle_limit(double *angle)
{
	if (*angle < 0)
		*angle = (2 * PI) + *angle;
	else if (*angle > (PI * 2))
		*angle = *angle - (2 * PI);
}
