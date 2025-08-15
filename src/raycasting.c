/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:21:29 by skully            #+#    #+#             */
/*   Updated: 2025/08/15 18:01:09 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_check_limits(t_vect2 *len)
{
    if(len->x > SCREEN_WIDTH)
        len->x = SCREEN_WIDTH;
    else if(len->x < 0)
        len->x = 0;
    if(len->y > SCREEN_HEIGHT)
        len->y = SCREEN_HEIGHT;
    else if(len->y < 0)
        len->y = 0;
}

t_vect2 hori_first_point(t_cube *cube)
{
    t_vect2 len;

    if(cube->player.ray.y_dir == DOWN)
    {
        len.y = ((cube->player.grid_y + 1) * GRID_SIZE) - cube->player.y;
        len.x = (len.y * (1 / tan(cube->player.ray.angle)));
        len.y += cube->player.y;
        if(cube->player.ray.x_dir == RIGHT)
            len.x += cube->player.x;
        else
            len.x = cube->player.x - len.x;
    }
    else if(cube->player.ray.y_dir == UP)
    {
        len.y = cube->player.y - (cube->player.grid_y * GRID_SIZE);
        len.x = (len.y * (1 / tan(cube->player.ray.angle)));
        len.y = cube->player.y - len.y;
        if(cube->player.ray.x_dir == RIGHT)
            len.x += cube->player.x;
        else
            len.x = cube->player.x - len.x;
    }
    ft_check_limits(&len);
    return len;
}

t_vect2 vert_first_point(t_cube *cube)
{
    t_vect2 len;

    if(cube->player.ray.x_dir == RIGHT)
    {
        len.x = ((cube->player.grid_x + 1) * GRID_SIZE) - cube->player.x;
        len.y = len.x * tan(cube->player.ray.angle);
        len.x += cube->player.x;
        if(cube->player.ray.y_dir == UP)
            len.y = cube->player.y - len.y;
        else
            len.y += cube->player.y;
    }
    else if(cube->player.ray.x_dir == LEFT)
    {
        len.x = cube->player.x - (cube->player.grid_x * GRID_SIZE);
        len.y = len.x * tan(cube->player.ray.angle);
        len.x = cube->player.x - len.x;
        if(cube->player.ray.y_dir == UP)
            len.y = cube->player.y - len.y;
        else
            len.y += cube->player.y;
    }
    ft_check_limits(&len);
    return len;
}
