/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2025/10/02 09:26:35 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <fcntl.h>
// #include <error.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define RES 800
#define FOV 70
#define PI 3.14159265359
#define RADIANT_RATE PI / 180
#define GRID_SIZE 20
#define WALL_DST 2
#define WALL_SCALE SCREEN_HEIGHT / 2
#define TURN_SPEED 0.001
#define PLAYER_SPEED 1
#define HORI 0
#define VERT 1
#define MAP_X 30
#define MAP_Y 30
#define PERP_DST SCREEN_HEIGHT * (0.5 * GRID_SIZE / tan((FOV / 2) * RADIANT_RATE))

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
    int grid_x;
    int grid_y;
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
    double normal_dst;
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
    mlx_texture_t *texture;
}   t_cube;

#endif



bool ft_check_limits(t_vect2 len);
void ft_limit_cords(t_vect2 *len);
t_vect2 hori_first_point(t_cube *cube, t_ray *ray);
t_vect2 vert_first_point(t_cube *cube, t_ray *ray);