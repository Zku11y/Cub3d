/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by skully            #+#    #+#             */
/*   Updated: 2025/07/31 14:59:07 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void clear_image(t_cube *cube)
{
    int buffer_size = SCREEN_HEIGHT * SCREEN_WIDTH * 4;
    ft_memset(cube->image->pixels, 0, buffer_size);
}

void draw_player(t_cube *cube)
{
    int offset = 3;
    int x = cube->pos.x - offset;
    int y;
    while(x < (cube->pos.x + (offset * 2)))
    {
        y = cube->pos.y - offset;
        while(y < (cube->pos.y + (offset * 2)))
        {
            mlx_put_pixel(cube->image, x, y, 0xff1100ff);
            y++;
        }
        x++;
    }
}

void ft_key_hook(mlx_key_data_t keydata, void* param)
{
    t_cube *cube;

    cube = (t_cube *)param;
    if(keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
        cube->moving = true;
    else if(keydata.action == MLX_RELEASE)
        cube->moving = false;
    if(cube->moving == true)
    {
        if(keydata.key == MLX_KEY_W)
            cube->pos.y -= 5;
        else if(keydata.key == MLX_KEY_S)
            cube->pos.y += 5;
        else if(keydata.key == MLX_KEY_D)
            cube->pos.x += 5;
        else if(keydata.key == MLX_KEY_A)
            cube->pos.x -= 5;
    }
}

void get_input(t_cube *cube)
{
    mlx_key_hook(cube->mlx, ft_key_hook, cube);
}

void ft_update(void *param)
{
    t_cube *cube;

    cube = (t_cube *)param;
    clear_image(cube);
    draw_player(cube);
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);    
}

int main()
{
    t_cube cube;

    cube.moving = false;
    cube.pos.x = SCREEN_WIDTH / 2;
    cube.pos.y = SCREEN_HEIGHT / 2;
    cube.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    cube.image = mlx_new_image(cube.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_loop_hook(cube.mlx, ft_update, &cube);
    get_input(&cube);
    mlx_loop(cube.mlx);
    mlx_terminate(cube.mlx);
    return 0;
}