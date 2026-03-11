/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:55:52 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 01:11:15 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	ft_safe_tan(double angle)
{
	double	result;

	result = tan(angle);
	if (fabs(result) < 0.00001)
		return (0.00001);
	return (result);
}

void	vert_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray,
		double add)
{
	while (ft_check_limits(cube, *start) == false)
	{
		if (check_collision(cube, start, VERT, ray) == true)
			return ;
		if (ray->x_dir == RIGHT)
			start->x = start->x + GRID_SIZE;
		else
			start->x = start->x - GRID_SIZE;
		if (ray->y_dir == UP)
			start->y = start->y - add;
		else
			start->y = start->y + add;
	}
}

void	hori_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray,
		double add)
{
	while (ft_check_limits(cube, *start) == false)
	{
		if (check_collision(cube, start, HORI, ray) == true)
			return ;
		if (ray->y_dir == DOWN)
			start->y = start->y + GRID_SIZE;
		else
			start->y = start->y - GRID_SIZE;
		if (ray->x_dir == RIGHT)
			start->x = start->x + add;
		else
			start->x = start->x - add;
	}
}

void	ft_limit_cords(t_cube *cube, t_vect2 *len)
{
	if (len->x > cube->map_x * GRID_SIZE)
		len->x = cube->map_x * GRID_SIZE;
	else if (len->x < 0)
		len->x = 0;
	if (len->y > cube->map_y * GRID_SIZE)
		len->y = cube->map_y * GRID_SIZE;
	else if (len->y < 0)
		len->y = 0;
}

bool	ft_check_limits(t_cube *cube, t_vect2 len)
{
	if (len.x > cube->map_x * GRID_SIZE)
		return (true);
	else if (len.x < 0)
		return (true);
	if (len.y > cube->map_y * GRID_SIZE)
		return (true);
	else if (len.y < 0)
		return (true);
	return (false);
}
