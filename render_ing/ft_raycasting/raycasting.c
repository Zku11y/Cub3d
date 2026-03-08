/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:21:29 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:51:19 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	hori_extra(t_cube *cube, t_ray *ray, t_vect2 *len, double *inv_tan)
{
	len->y = ((cube->player.grid_y + 1) * GRID_SIZE) - cube->player.y;
	len->x = fabs(len->y * *inv_tan);
	len->y += cube->player.y;
	if (ray->x_dir == RIGHT)
		len->x += cube->player.x;
	else
		len->x = cube->player.x - len->x;
}

t_vect2	hori_first_point(t_cube *cube, t_ray *ray)
{
	t_vect2	len;
	double	add;
	double	inv_tan;

	len = (t_vect2){0, 0, 0, 0};
	if (fabs(tan(ray->angle)) < 0.000001)
		inv_tan = 1e30;
	else
		inv_tan = 1.0 / tan(ray->angle);
	if (ray->y_dir == DOWN)
		hori_extra(cube, ray, &len, &inv_tan);
	else if (ray->y_dir == UP)
	{
		len.y = cube->player.y - (cube->player.grid_y * GRID_SIZE);
		len.x = fabs(len.y * inv_tan);
		len.y = cube->player.y - len.y;
		if (ray->x_dir == RIGHT)
			len.x += cube->player.x;
		else
			len.x = cube->player.x - len.x;
	}
	ft_limit_cords(cube, &len);
	add = fabs(GRID_SIZE * inv_tan);
	hori_check_next_point(cube, &len, ray, add);
	return (len);
}

void	vert_extra(t_cube *cube, t_ray *ray, t_vect2 *len, double *s_tan)
{
	len->x = ((cube->player.grid_x + 1) * GRID_SIZE) - cube->player.x;
	len->y = fabs(len->x * *s_tan);
	len->x += cube->player.x;
	if (ray->y_dir == UP)
		len->y = cube->player.y - len->y;
	else
		len->y += cube->player.y;
}

t_vect2	vert_first_point(t_cube *cube, t_ray *ray)
{
	t_vect2	len;
	double	add;
	double	s_tan;

	len = (t_vect2){0, 0, 0, 0};
	s_tan = tan(ray->angle);
	if (ray->x_dir == RIGHT)
		vert_extra(cube, ray, &len, &s_tan);
	else if (ray->x_dir == LEFT)
	{
		len.x = cube->player.x - (cube->player.grid_x * GRID_SIZE);
		len.y = fabs(len.x * s_tan);
		len.x = cube->player.x - len.x;
		if (ray->y_dir == UP)
			len.y = cube->player.y - len.y;
		else
			len.y += cube->player.y;
	}
	ft_limit_cords(cube, &len);
	add = fabs(GRID_SIZE * s_tan);
	vert_check_next_point(cube, &len, ray, add);
	return (len);
}
