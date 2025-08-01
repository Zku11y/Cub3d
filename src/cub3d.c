/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by skully            #+#    #+#             */
/*   Updated: 2025/08/01 17:41:00 by skully           ###   ########.fr       */
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
    int y;
    int x;
    int offset;

    offset = 3;
    if(cube->pos.x < offset)
        cube->pos.x = offset;
    else if(cube->pos.x > SCREEN_WIDTH)
        cube->pos.x = SCREEN_WIDTH - offset;
    if(cube->pos.y < offset)
        cube->pos.y = offset;
    else if(cube->pos.y > SCREEN_HEIGHT)
        cube->pos.y = SCREEN_HEIGHT - offset;
    x = cube->pos.x - offset;
    while(x < (cube->pos.x + offset))
    {
        y = cube->pos.y - offset;
        while(y < (cube->pos.y + offset))
        {
            mlx_put_pixel(cube->image, x, y, 0xff1100ff);
            y++;
        }
        x++;
    }
}

void draw_grid(t_cube *cube)
{
    int x = 0;
    int y = 0;
    while(x < SCREEN_WIDTH)
    {
        mlx_put_pixel(cube->image, x, 1, 0x000000ff);
        mlx_put_pixel(cube->image, x, 2, 0x000000ff);
        mlx_put_pixel(cube->image, x, 3, 0x000000ff);
        mlx_put_pixel(cube->image, x, SCREEN_HEIGHT - 1, 0x000000ff);
        mlx_put_pixel(cube->image, x, SCREEN_HEIGHT - 2, 0x000000ff);
        mlx_put_pixel(cube->image, x, SCREEN_HEIGHT - 3, 0x000000ff);
        x++;
    }
    while(y < SCREEN_HEIGHT)
    {
        mlx_put_pixel(cube->image, 1, y, 0x000000ff);
        mlx_put_pixel(cube->image, 2, y, 0x000000ff);
        mlx_put_pixel(cube->image, 3, y, 0x000000ff);
        mlx_put_pixel(cube->image, SCREEN_WIDTH - 1, y, 0x000000ff);
        mlx_put_pixel(cube->image, SCREEN_WIDTH - 2, y, 0x000000ff);
        mlx_put_pixel(cube->image, SCREEN_WIDTH - 3, y, 0x000000ff);
        y++;
    }
}

void ft_update(void *param)
{
    t_cube *cube;

    cube = (t_cube *)param;
    clear_image(cube);
    draw_grid(cube);
    if(mlx_is_key_down(cube->mlx, MLX_KEY_W))
        cube->pos.y -= 5;
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_S))
        cube->pos.y += 5;
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_D))
        cube->pos.x += 5;
    else if(mlx_is_key_down(cube->mlx, MLX_KEY_A))
        cube->pos.x -= 5;
    draw_player(cube);
    //    usleep(16000);
}  

int main()
{
    t_cube cube;
    
    cube.moving = false;
    cube.pos.x = SCREEN_WIDTH / 2;
    cube.pos.y = SCREEN_HEIGHT / 2;
    cube.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    cube.image = mlx_new_image(cube.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx_image_to_window(cube.mlx, cube.image, 0, 0);
    mlx_loop_hook(cube.mlx, ft_update, &cube);
    mlx_loop(cube.mlx);
    mlx_terminate(cube.mlx);
    return 0;
}