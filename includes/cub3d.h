/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2025/08/10 19:36:36 by skully           ###   ########.fr       */
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


typedef struct s_vect2
{
    double x;
    double y;
}   t_vect2;

typedef struct s_player
{
    int x;
    int y;
    float angle;
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