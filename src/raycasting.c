/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 12:21:29 by skully            #+#    #+#             */
/*   Updated: 2026/02/07 15:26:42 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double ft_safe_tan(double angle){
    double result;

    result = tan(angle);
    if(fabs(result) < 0.00001)
        return 0.00001;
    return result;
}

bool check_collision(t_cube *cube, t_vect2 *cords, bool hori_vert, t_ray *ray)
{
    t_vect2 grid_cords;

    grid_cords.x = 0;
    grid_cords.y = 0;
    if(hori_vert == HORI)
    {
        if(ray->y_dir == DOWN)
        {
            grid_cords.y = cords->y / GRID_SIZE;             
            grid_cords.x = cords->x / GRID_SIZE;
        }
        else if(ray->y_dir == UP)
        {
            grid_cords.y = cords->y / GRID_SIZE;
            grid_cords.x = cords->x / GRID_SIZE;
            if(grid_cords.y > 0)
                grid_cords.y -= 1;
        }
    }
    else
    {
        if(ray->x_dir == RIGHT)
        {
            grid_cords.y = cords->y / GRID_SIZE;             
            grid_cords.x = cords->x / GRID_SIZE;
        }
        else
        {
            grid_cords.y = cords->y / GRID_SIZE;
            grid_cords.x = cords->x / GRID_SIZE;
            if(grid_cords.x > 0)
                grid_cords.x -= 1;
        }
    }
    if((int)grid_cords.x >= MAP_X)
        grid_cords.x = MAP_X - 1;
    if((int)grid_cords.y >= MAP_Y)
        grid_cords.y = MAP_Y - 1;
    if(cube->map[(int)grid_cords.y][(int)grid_cords.x] == 1)
        return (cords->grid_x = grid_cords.x, cords->grid_y = grid_cords.y, true);
    return false;
}

void ft_limit_cords(t_vect2 *len)
{
    if(len->x > MAP_X * GRID_SIZE)
        len->x = MAP_X * GRID_SIZE;
    else if(len->x < 0)
        len->x = 0;
    if(len->y > MAP_Y * GRID_SIZE)
        len->y = MAP_Y * GRID_SIZE;
    else if(len->y < 0)
        len->y = 0;
}

bool ft_check_limits(t_vect2 len)
{
    if(len.x > MAP_X * GRID_SIZE)
        return true;
    else if(len.x < 0)
        return true;
    if(len.y > MAP_Y * GRID_SIZE)
        return true;
    else if(len.y < 0)
        return true;
    return false;
}

void vert_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray, double add)
{
    while(ft_check_limits(*start) == false)
    {
        if(check_collision(cube, start, VERT, ray) == true)
            return;
        if(ray->x_dir == RIGHT)
            start->x = start->x + GRID_SIZE;
        else
            start->x = start->x - GRID_SIZE;
        if(ray->y_dir == UP)
            start->y = start->y - add;
        else
            start->y = start->y + add;
    }
}

void hori_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray, double add)
{
    while(ft_check_limits(*start) == false)
    {
        if(check_collision(cube, start, HORI, ray) == true)
            return;
        if(ray->y_dir == DOWN)
            start->y = start->y + GRID_SIZE;
        else
            start->y = start->y - GRID_SIZE;
        if(ray->x_dir == RIGHT)
            start->x = start->x + add;
        else
            start->x = start->x - add;
    }
}

t_vect2 hori_first_point(t_cube *cube, t_ray *ray)
{
    t_vect2 len = {0};
    double add;
    double inv_tan;

    if (fabs(tan(ray->angle)) < 0.000001)
        inv_tan = 1e30;
    else
        inv_tan = 1.0 / tan(ray->angle);

    if(ray->y_dir == DOWN)
    {
        len.y = ((cube->player.grid_y + 1) * GRID_SIZE) - cube->player.y;
        len.x = fabs(len.y * inv_tan);
        len.y += cube->player.y;
        if(ray->x_dir == RIGHT)
            len.x += cube->player.x;
        else
            len.x = cube->player.x - len.x;
    }
    else if(ray->y_dir == UP)
    {
        len.y = cube->player.y - (cube->player.grid_y * GRID_SIZE);
        len.x = fabs(len.y * inv_tan);
        len.y = cube->player.y - len.y;
        if(ray->x_dir == RIGHT)
            len.x += cube->player.x;
        else
            len.x = cube->player.x - len.x;
    }
    ft_limit_cords(&len);
    add = fabs(GRID_SIZE * inv_tan);
    hori_check_next_point(cube, &len, ray, add);
    return len;
}

t_vect2 vert_first_point(t_cube *cube, t_ray *ray)
{
    t_vect2 len = {0};
    double add;
    double s_tan;

    s_tan = tan(ray->angle);

    if(ray->x_dir == RIGHT)
    {
        len.x = ((cube->player.grid_x + 1) * GRID_SIZE) - cube->player.x;
        len.y = fabs(len.x * s_tan);
        len.x += cube->player.x;
        if(ray->y_dir == UP)
            len.y = cube->player.y - len.y;
        else
            len.y += cube->player.y;
    }
    else if(ray->x_dir == LEFT)
    {
        len.x = cube->player.x - (cube->player.grid_x * GRID_SIZE);
        len.y = fabs(len.x * s_tan);
        len.x = cube->player.x - len.x;
        if(ray->y_dir == UP)
            len.y = cube->player.y - len.y;
        else
            len.y += cube->player.y;
    }
    ft_limit_cords(&len);
    add = fabs(GRID_SIZE * s_tan);
    vert_check_next_point(cube, &len, ray, add);
    return len;
}


