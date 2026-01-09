/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2026/01/09 17:47:02 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
// #include <error.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
// 1920 / 4 = 480 || 1080 / 4 = 270
# define UPSCALING_RATE 3
# define SCREEN_WIDTH_BUFF 1280
# define SCREEN_HEIGHT_BUFF 720
# define SCREEN_WIDTH (SCREEN_WIDTH_BUFF / UPSCALING_RATE)
# define SCREEN_HEIGHT (SCREEN_HEIGHT_BUFF / UPSCALING_RATE)
# define RES SCREEN_WIDTH
# define FOV 70
# define PI 3.14159265359
// # define PI 420.67
# define RADIANT_RATE (PI / 180)
# define WALL_DST 2
# define WALL_SCALE (SCREEN_HEIGHT / 2)
# define TURN_SPEED 0.001
# define GRID_SIZE 64.0f
# define PLAYER_SPEED 500.0f
# define HORI 0
# define VERT 1
# define MAP_X 25
# define MAP_Y 25
# define MAX_DST 1000
# define PROJ_DST (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * RADIANT_RATE)
# define HALF_FOV_RAD tan((FOV / 2.0) * RADIANT_RATE)
# define CAM_H (GRID_SIZE / 2.0)
# define LERP 0.4
# define SPEED_LERP 0.1
# define PITCH_MAX (SCREEN_HEIGHT + 100)
# define MINI_MAP_X 50
# define MINI_MAP_Y 50
# define MAP_SIZE 100
# define ENEMY_RADIUS 10.0
# define ENEMY_SPEED 1
# define ENEMY_NUM 50
# define CROSSHAIR_LEN 7.0
# define CROSSHAIR_GIRTH 1.0
# define CROSSHAIR_COLOR 0xff0000ff
# define MIN_ATK_DST 10
typedef enum s_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}					t_direction;

typedef enum s_state
{
	GAME,
	MENU,
	DIED
}					t_state;
typedef struct s_vect2
{
	double			x;
	double			y;
	int				grid_x;
	int				grid_y;
}					t_vect2;

typedef struct s_ray
{
	t_vect2			start;
	t_vect2			end;
	double			length;
	t_direction		x_dir;
	t_direction		y_dir;
	double			angle;
	double			real_angle;
	double			normal_dst;
	bool			collision;
}					t_ray;
typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	int				grid_x;
	int				grid_y;
	t_ray			ray;
	double			current_speed_LR_X; 
	double			current_speed_LR_Y;
	double			current_speed_FB_X; 
	double			current_speed_FB_Y;
	t_direction		last_LR;
	t_direction		last_FB;
	int				HP;
	int				DMG;
	int				atk_delay;
	unsigned long	atk_time;
	bool			delay;
}					t_player;

typedef struct s_enemy
{
	double 			x;
	double 			y;
	int				HP;
	int				DMG;
	int				atk_delay;
	unsigned long	atk_time;
	bool			delay;
	bool			dead;
	double			player_dst;
}					t_enemy;

typedef struct s_cube
{
	mlx_t			*mlx;

	char			**map;
	char			**floor_map;
	t_ray			*rays;
	mlx_image_t		*image;
	mlx_image_t		*image_death;
	mlx_image_t		*image_menu;
	t_vect2			pos;
	t_player		player;
	bool			moving;
	unsigned long	init_t;
	unsigned long	final_t;
	int				fps;
	double			mod_rate;
	int				line_girth;
	mlx_texture_t	*texture;
	mlx_texture_t	*texture2;
	mlx_texture_t	*texture3;
	mlx_texture_t	*texture4;
	mlx_texture_t	*texture5;
	mlx_texture_t	*texture6;
	mlx_texture_t	*texture_died;
	double			min_length;
	int8_t			*prev_buffer;
	int8_t			*lerp_buffer;
	t_enemy			*enemy;
	bool			grain;
	double			pitch;
	double			*z_buffer;
	t_vect2			crosshair_vert_start;
	t_vect2			crosshair_vert_end;
	t_vect2			crosshair_hori_start;
	t_vect2			crosshair_hori_end;
	t_state			state;
	t_state			prev_state;
}					t_cube;

#endif

bool				ft_check_limits(t_vect2 len);
void				ft_limit_cords(t_vect2 *len);
t_vect2				hori_first_point(t_cube *cube, t_ray *ray);
t_vect2				vert_first_point(t_cube *cube, t_ray *ray);