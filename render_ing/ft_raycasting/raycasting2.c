/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:55:47 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/09 21:18:47 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_collision1(t_cube *cube, t_vect2 *cords, t_ray *ray,
		t_vect2 *grid_cords)
{
	if (ray->y_dir == DOWN)
	{
		grid_cords->y = cords->y / GRID_SIZE;
		grid_cords->x = cords->x / GRID_SIZE;
		// ray->texture = cube->nu->txtrs[1];
	}
	else if (ray->y_dir == UP)
	{
		grid_cords->y = cords->y / GRID_SIZE;
		grid_cords->x = cords->x / GRID_SIZE;
		if (grid_cords->y > 0)
			grid_cords->y -= 1;
		// ray->texture = cube->nu->txtrs[0];
	}
}

void	check_collision2(t_cube *cube, t_vect2 *cords, t_ray *ray,
		t_vect2 *grid_cords)
{
	if (ray->x_dir == RIGHT)
	{
		grid_cords->y = cords->y / GRID_SIZE;
		grid_cords->x = cords->x / GRID_SIZE;
		// ray->texture = cube->nu->txtrs[3];
	}
	else
	{
		grid_cords->y = cords->y / GRID_SIZE;
		grid_cords->x = cords->x / GRID_SIZE;
		if (grid_cords->x > 0)
			grid_cords->x -= 1;
		// ray->texture = cube->nu->txtrs[2];
	}
}

bool	check_collision(t_cube *cube, t_vect2 *cords, bool hori_vert,
		t_ray *ray)
{
	t_vect2	grid_cords;
	char	result;

	grid_cords.x = 0;
	grid_cords.y = 0;
	if (hori_vert == HORI)
		check_collision1(cube, cords, ray, &grid_cords);
	else
		check_collision2(cube, cords, ray, &grid_cords);
	if ((int)grid_cords.x >= cube->map_x)
		grid_cords.x = cube->map_x - 1;
	if ((int)grid_cords.y >= cube->map_y)
		grid_cords.y = cube->map_y - 1;
	result = cube->map[(int)grid_cords.y][(int)grid_cords.x];
	if (result == '1' || result == 'D') {
        if (result == 'D') {
            if (hori_vert == HORI)
                ray->hori_obstacle = 'H';
            else
                ray->vert_obstacle = 'V';
        } else {
            if (hori_vert == HORI)
                ray->hori_obstacle = '1';
            else
                ray->vert_obstacle = '1';
        }
		// else if(hori_vert == HORI && ray->y_dir == DOWN)
		// 	ray->texture = cube->nu->txtrs[0];
		// else if(hori_vert == HORI && ray->y_dir == UP)
		// 	ray->texture = cube->nu->txtrs[1];
		// else if(hori_vert == VERT && ray->x_dir == LEFT)
		// 	ray->texture = cube->nu->txtrs[2];
		// else if(hori_vert == VERT && ray->x_dir == RIGHT)
		// 	ray->texture = cube->nu->txtrs[3];
		return (cords->grid_x = grid_cords.x, cords->grid_y = grid_cords.y,
			true);
	}
	if(hori_vert == HORI)
		ray->hori_obstacle = '0';
	else if(hori_vert == VERT)
		ray->vert_obstacle = '0';
	return (false);
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
