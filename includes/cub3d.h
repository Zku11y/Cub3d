/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2025/08/18 12:33:27 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <fcntl.h>
#include <error.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define PI 3.14159265359
#define GRID_SIZE 50
#define WALL_DST 2
#define TURN_SPEED 0.02
#define PLAYER_SPEED 2
#define HORI 0
#define VERT 1

typedef enum s_direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
} t_direction;

typedef struct s_vect2
{
    double x;
    double y;
}   t_vect2;

typedef struct s_ray
{
    t_vect2 start;
    t_vect2 end;
    double length;
    t_direction x_dir;
    t_direction y_dir;
    double angle;
    bool contact;
} t_ray;
typedef struct s_player
{
    int x;
    int y;
    t_vect2 pos;
    float angle;
    int grid_x;
    int grid_y;
    t_ray ray;
}   t_player;

typedef struct s_cube
{
    mlx_t *mlx;

    char **map;
    mlx_image_t *image;
    t_vect2 pos;
    t_player player;
    bool moving;
    int map_x;
    int map_y;
    unsigned long init_t;
    unsigned long final_t;
    int fps;
}   t_cube;

#endif




t_vect2 hori_first_point(t_cube *cube);
t_vect2 vert_first_point(t_cube *cube);