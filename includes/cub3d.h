/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2025/08/23 15:45:22 by skully           ###   ########.fr       */
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

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define RES 500
#define FOV 50
#define PI 3.14159265359
#define RADIANT_RATE PI / 180
#define GRID_SIZE 20
#define WALL_DST 2
#define WALL_SCALE SCREEN_HEIGHT / 2
#define TURN_SPEED 0.0009
#define PLAYER_SPEED 1.2
#define HORI 0
#define VERT 1
#define MAP_X 30
#define MAP_Y 30

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
    double real_angle;
} t_ray;
typedef struct s_player
{
    double x;
    double y;
    t_vect2 pos;
    double angle;
    int grid_x;
    int grid_y;
    t_ray ray;
}   t_player;

typedef struct s_cube
{
    mlx_t *mlx;

    char **map;
    t_ray *rays;
    mlx_image_t *image;
    t_vect2 pos;
    t_player player;
    bool moving;
    unsigned long init_t;
    unsigned long final_t;
    int fps;
    double mod_rate;
    int line_girth;
}   t_cube;

#endif




t_vect2 hori_first_point(t_cube *cube, t_ray *ray);
t_vect2 vert_first_point(t_cube *cube, t_ray *ray);