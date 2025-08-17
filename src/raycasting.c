/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:21:29 by skully            #+#    #+#             */
/*   Updated: 2025/08/17 15:00:52 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool check_collision(t_cube *cube, t_vect2 cords, bool hori_vert)
{
    t_vect2 grid_cords;

    grid_cords.x = 0;
    grid_cords.y = 0;
    if(hori_vert == HORI)
    {
        if(cube->player.ray.y_dir == DOWN)
        {
            grid_cords.y = cords.y / GRID_SIZE;             
            grid_cords.x = cords.x / GRID_SIZE;
        }
        else if(cube->player.ray.y_dir == UP)
        {
            grid_cords.y = cords.y / GRID_SIZE;
            grid_cords.x = cords.x / GRID_SIZE;
            if(grid_cords.y > 0)
                grid_cords.y -= 1;
        }
    }
    else
    {
        if(cube->player.ray.x_dir == RIGHT)
        {
            grid_cords.y = cords.y / GRID_SIZE;             
            grid_cords.x = cords.x / GRID_SIZE;
        }
        else
        {
            grid_cords.y = cords.y / GRID_SIZE;
            grid_cords.x = cords.x / GRID_SIZE;
            if(grid_cords.x > 0)
                grid_cords.x -= 1;
        }
    }
    if((int)grid_cords.x >= cube->map_x)
        grid_cords.x = cube->map_x - 1;
    if((int)grid_cords.y >= cube->map_y)
        grid_cords.y = cube->map_y - 1;
    // printf("grid : (%d, %d), cords : (%d, %d)\n", (int)grid_cords.x, (int)grid_cords.y, (int)cords.x, (int)cords.y);
    if(cube->map[(int)grid_cords.y][(int)grid_cords.x] == 1)
        return true;
    return false;
}

void ft_limit_cords(t_cube *cube ,t_vect2 *len)
{
    if(len->x > cube->map_x * GRID_SIZE)
        len->x = cube->map_x * GRID_SIZE;
    else if(len->x < 0)
        len->x = 0;
    if(len->y > cube->map_y * GRID_SIZE)
        len->y = cube->map_y * GRID_SIZE;
    else if(len->y < 0)
        len->y = 0;
}

bool ft_check_limits(t_cube *cube, t_vect2 len)
{
    if(len.x > cube->map_x * GRID_SIZE)
        return true;
    else if(len.x < 0)
        return true;
    if(len.y > cube->map_y * GRID_SIZE)
        return true;
    else if(len.y < 0)
        return true;
    return false;
}

void vert_check_next_point(t_cube *cube, t_vect2 *start)
{
    while(ft_check_limits(cube, *start) == false)
    {
        if(check_collision(cube, *start, VERT) == true)
            return;
        if(cube->player.ray.x_dir == RIGHT)
            start->x = start->x + GRID_SIZE;
        else
            start->x = start->x - GRID_SIZE;
        if(cube->player.ray.y_dir == UP)
            start->y = start->y - GRID_SIZE * tan(cube->player.ray.angle);
        else
            start->y = start->y + GRID_SIZE * tan(cube->player.ray.angle);
    }
}

void hori_check_next_point(t_cube *cube, t_vect2 *start)
{
    while(ft_check_limits(cube, *start) == false)
    {
        if(check_collision(cube, *start, HORI) == true)
            return;
        if(cube->player.ray.y_dir == DOWN)
            start->y = start->y + GRID_SIZE;
        else
            start->y = start->y - GRID_SIZE;
        if(cube->player.ray.x_dir == RIGHT)
            start->x = start->x + (GRID_SIZE * (1 / tan(cube->player.ray.angle)));
        else
            start->x = start->x - (GRID_SIZE * (1 / tan(cube->player.ray.angle)));
        // mlx_put_pixel(cube->image, start->x, start->y, 0x0d00ff00);
    }
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
    ft_limit_cords(cube, &len);
    // check_collision(cube, len, HORI);
    hori_check_next_point(cube, &len);
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
    ft_limit_cords(cube, &len);
    vert_check_next_point(cube, &len);
    return len;
}


