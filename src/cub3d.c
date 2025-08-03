/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by skully            #+#    #+#             */
/*   Updated: 2025/08/03 18:24:46 by skully           ###   ########.fr       */
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

void draw_line(t_cube *cube, int start, int finish, int cst, bool axis_x)
{
    int i;

    i = start;
    while(i < finish)
    {
        if(axis_x)
            mlx_put_pixel(cube->image, i, cst, 0xffffffff);
        else
            mlx_put_pixel(cube->image, cst, i, 0xffffffff);
        i++;
    }
}

void draw_grid(t_cube *cube)
{
    int y = 0;
    int x = 0;

    while(y < cube->map_y)
    {
        x = 0;
        while(x < cube->map_x)
        {
            if(cube->map[y][x] == 1)
            {
                if(y == 0 || cube->map[y - 1][x] == 0)
                    draw_line(cube, x * 50, (x + 1) * 50, y * 50, true);
                if(y == cube->map_y - 1 || cube->map[y + 1][x] == 0)
                    draw_line(cube, x * 50, (x + 1) * 50, (y + 1) * 50, true);
                if(x == 0 || cube->map[y][x - 1] == 0)
                    draw_line(cube, y * 50, (y + 1) * 50, x * 50, false);
                if(x == cube->map_x - 1 || cube->map[y][x + 1] == 0)
                    draw_line(cube, y * 50, (y + 1) * 50, (x + 1) * 50, false);
            }
            x++;
        }
        y++;
    }
}

void ft_update(void *param)
{
    t_cube *cube;
    struct timeval tv;

    cube = (t_cube *)param;
    cube->fps++;
    gettimeofday(&tv, NULL);
    cube->final_t = tv.tv_sec;
    if(cube->final_t - cube->init_t == 1)
    {
        printf("fps : %d\n", cube->fps);
        cube->init_t = cube->final_t;
        cube->fps = 0;
    }
    clear_image(cube);
    // printf("start here\n");
    // printf("start here\n");
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
    //    usleep(12000);
}  

void ft_parse(t_cube *cube)
{
    int i = 0;
    int j = 0;
    while(i < 10)
    {
        j = 0;
        while(j < 10)
        {
            printf("i : %d, j : %d, value : %d\n", i, j, cube->map[i][j]);
            j++;
        }
        i++;
    }
}

void ft_map_init(t_cube *cube)
{
    cube->map_x = 10;
    cube->map_y = 10;
    cube->map = ft_calloc(cube->map_y + 1, sizeof(char *));
    if(cube->map == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("Alloc error : ");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while(i < cube->map_y)
    {
        cube->map[i] = ft_calloc(cube->map_x + 1, sizeof(char));
        i++;
    }
    i = 0;
    while(i < cube->map_x)
    {
        cube->map[0][i] = 1;
        cube->map[i][0] = 1;
        cube->map[cube->map_y - 1][i] = 1;
        cube->map[i][cube->map_x - 1] = 1;
        i++;
    }
}

void ft_init(t_cube *cube)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    cube->fps = 0;
    cube->init_t = tv.tv_sec;
    cube->final_t = tv.tv_sec;
    cube->moving = false;
    cube->pos.x = SCREEN_WIDTH / 2;
    cube->pos.y = SCREEN_HEIGHT / 2;
    cube->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", true);
    if(cube->mlx == NULL)
    {
        perror("mlx init error :");
        exit(EXIT_FAILURE);
    }
    cube->image = mlx_new_image(cube->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if(cube->image == NULL)
    {
        mlx_terminate(cube->mlx);
        perror("image init error :");
        exit(EXIT_FAILURE);
    }
    mlx_image_to_window(cube->mlx, cube->image, 0, 0);
}

int main()
{
    t_cube cube;
    ft_map_init(&cube);
    // ft_parse(&cube);
    ft_init(&cube);
    mlx_loop_hook(cube.mlx, ft_update, &cube);
    mlx_loop(cube.mlx);
    mlx_terminate(cube.mlx);
    return 0;
}
