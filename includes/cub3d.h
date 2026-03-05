/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2026/03/05 21:50:05 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
// # include "miniaudio.h"
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

# include "../pars_ing/head.h"

# define UPSCALING_RATE 4
# define SCREEN_WIDTH_BUFF 1600
# define SCREEN_HEIGHT_BUFF 900
# define SCREEN_WIDTH (SCREEN_WIDTH_BUFF / UPSCALING_RATE)
# define SCREEN_HEIGHT (SCREEN_HEIGHT_BUFF / UPSCALING_RATE)
# define RES SCREEN_WIDTH
# define FOV 70
# define PI 3.14159265359
# define RADIANT_RATE (PI / 180)
# define WALL_DST 5
# define TURN_SPEED 0.0015
# define GRID_SIZE 32.0f
# define PLAYER_SPEED 200.0f
# define HORI 0
# define VERT 1
# define MAP_X 30
# define MAP_Y 30
# define MAX_DST 200
# define PROJ_DST (SCREEN_WIDTH / 2.0) / tan((FOV / 2.0) * RADIANT_RATE)
# define HALF_FOV_RAD tan((FOV / 2.0) * RADIANT_RATE)
# define CAM_H (GRID_SIZE / 2.0)
# define MAX_HP 200
# define BLUR_MAX 0.06
# define BLUR_MIN 0.5
# define BLUR_LERP BLUR_MIN
# define SPEED_LERP 0.1
# define TILT_LERP 0.1
# define FOV_LERP 0.01
# define RECOIL_LERP 0.81
# define MOVE_LERP 0.1
# define FLASH_LERP 0.03
# define LERP_LERP 0.01
# define TRP_LERP 0.8
# define MOVE_INCREASE (0.05 * SCREEN_HEIGHT)
# define PITCH_MAX (SCREEN_HEIGHT + 100)
# define MINI_MAP_X 50
# define MINI_MAP_Y 50
# define MAP_SIZE 100
# define ENEMY_RADIUS 50.0
# define ENEMY_SPEED 1
# define ENEMY_NUM 7
# define CROSSHAIR_LEN 7.0
# define CROSSHAIR_GIRTH 1.0
# define CROSSHAIR_COLOR 0xffffffff
# define MIN_ATK_DST 150
# define MAX_PROJECTILES 100
# define MAX_RECOIL 30
# define HITBOX_DST 30
# define TILT_ANGLE 2
# define BLOOD_ANIM_DELAY 20
# define MINI_MAP_SIZE 400.0f
# define MINI_MAP_GRID_SIZE MINI_MAP_SIZE / GRID_SIZE

typedef enum s_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}					t_direction;

typedef enum s_weapon_type
{
	PISTOL,
	PUMP
}					t_weapon_type;

typedef struct s_weapon{

	int				DMG;
	int				fire_rate;
	int				delay;
	suseconds_t		frame_delay;
	mlx_texture_t	*texture;
	mlx_texture_t	*idle_texture;
	mlx_texture_t	*idle_texture_2;
	mlx_texture_t	*shoot_texture;
	mlx_texture_t	*pump_texture;
	double			pitch_og;
	double			pitch_increase;
	double			pitch_increased;
	bool			pitch_changed;
	bool			pitch_back;
	double			pitch_dst;
	unsigned long 	idle_time;
	bool 			idle_frame;
	double			move_lerp;
}					t_weapon;

typedef struct s_heart
{
	mlx_texture_t	*frame_1;
	mlx_texture_t	*frame_2;
	mlx_texture_t	*frame_3;
	mlx_texture_t	*frame_4;
	int				frame;
	unsigned long	prev_time;
	double			last_pitch;
	double			last_angle;
	double			added_angle;
	double			added_pitch;
	double			blur_lerp;
	double			blood_op; // op : Opacity, just used op for less lengthy code :P
}					t_heart;

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

typedef enum s_move_state{

	WALK,
	SPRINT,
	CROUCH,
	SLIDE
	
}					t_move_state;

typedef struct s_player
{
	double			x;
	double			y;
	double			angle;
	int				grid_x;
	int				grid_y;
	t_ray			ray;
	t_move_state    move_state;
	double			speed_mult;
	double			dst_speed_mult;
	double			current_speed_LR_X; 
	double			current_speed_LR_Y;
	double			current_speed_FB_X; 
	double			current_speed_FB_Y;
	double			dst_speed_LR_X; 
	double			dst_speed_LR_Y;
	double			dst_speed_FB_X; 
	double			dst_speed_FB_Y;
	t_direction		last_LR;
	t_direction		last_FB;
	int				HP;
	int				DMG;
	int				atk_delay;
	unsigned long	atk_time;
	bool			delay;
	t_weapon		weapon;
	bool			attacked;
	bool			hit;
}					t_player;

typedef struct s_blood_explosion
{
	mlx_texture_t *frame[12];

} t_blood_explosion;

typedef struct s_enemy
{
	double 			x;
	double 			y;
	int				HP;
	int				DMG;
	int				atk_delay;
	unsigned long	atk_time;
	unsigned long	blood_time;
	bool			delay;
	bool			dead;
	bool			health_spawn;
	double				health_offset;
	bool			health_animation;
	mlx_texture_t	*health;
	int				blood_frame_index;
	double			player_dst;
	int				start_y;
	int				end_y;
	int				start_x;
	int				end_x;
	int				hitbox_len;
	double			max_hit_angle;
}					t_enemy;

typedef struct s_projectile
{
	int				in_use;
	double			x;
	double 			y;
	t_vect2			dir;
	double			speed;
	double			dst_traveled;
	int 			DMG;
	mlx_texture_t	*texture;
}					t_projectile;

// typedef struct s_audio
// {
// 	ma_engine		engine;
// 	ma_sound		bg_start;
// 	ma_sound		bg_loop;
// }					t_audio;

typedef struct s_fov{
	mlx_texture_t	*bar_1;
	mlx_texture_t	*slider_1;
	int				slider_start_x;
	int				slider_end_x;
	int				slider_start_y;
	int				slider_end_y;
	int				min_fov;
	int				max_fov;
}					t_fov;

typedef struct s_resolution{

	mlx_texture_t	*texture;
	mlx_texture_t	*res_480_glow;
	mlx_texture_t	*res_720_glow;
	mlx_texture_t	*res_900_glow;
	mlx_texture_t	*res_1080_glow;
	int start_x_1080;
    int end_x_1080;
	int start_x_900;
    int end_x_900;
    int start_y_1080_900;
    int end_y_1080_900;
	int start_x_720;
    int end_x_720;
	int start_x_480;
    int end_x_480;
    int start_y_720_480;
    int end_y_720_480;

}					t_resolution;

typedef struct s_upscaling{

	mlx_texture_t	*texture;
	mlx_texture_t	*x1_glow;
	mlx_texture_t	*x2_glow;
	mlx_texture_t	*x3_glow;
	mlx_texture_t	*x4_glow;
	mlx_texture_t	*x5_glow;
	mlx_texture_t	*x6_glow;
	mlx_texture_t	*x7_glow;
	mlx_texture_t	*x8_glow;
	int				start_x15;
	int				start_x26;
	int				start_x37;
	int				start_x48;
	int				end_x15;
	int				end_x26;
	int				end_x37;
	int				end_x48;
	int				start_y1234;
	int				start_y5678;
	int				end_y1234;
	int				end_y5678;
}					t_upscaling;

typedef struct s_crosshair{

	int 			start_x;
	int			 	start_y;
	int 			end_x;
	int 			end_y;
	mlx_texture_t	*border;	
	int				color;
	
}					t_crosshair;

typedef struct s_mouse_sens{

	mlx_texture_t	*slider_2;
	int				slider_start_x;
	int				slider_end_x;
	int				slider_start_y;
	int				slider_end_y;
	double				min_sens;
	double				max_sens;

}					t_mouse_sens;

typedef enum s_held
{
	NOTHING,
	FOV_SLIDER,
	RESOLUTION,
	UPSCALING,
	CROSSHAIR,
	MOUSE_SENS_SLIDER
}	t_held;

typedef struct s_settings{

	mlx_texture_t	*background;
	mlx_texture_t	*bar_2;
	mlx_texture_t	*slider_2;
	t_held			mouse_held;
	t_fov			fov;
	t_resolution	resolution;
	t_crosshair		crosshair;
	t_mouse_sens	mouse_sens;
	t_upscaling		upscaling;

}	t_settings;

typedef struct s_menu{
	mlx_texture_t *title;
	mlx_texture_t *background;
	t_settings	   settings;
	int			   state;
}					t_menu;

typedef struct s_flash{

	double r;
	double g;
	double b;
	double dst_r;
	double dst_g;
	double dst_b;
	bool flashed;

}	t_flash;


typedef struct s_cube
{
	mlx_t			*mlx;

	int				screen_width;
	int				screen_height;
	int				screen_width_buff;
	int				screen_height_buff;
	double			camera_h;
	double			dst_camera_h;
	int				res;
	int				fov;
	int				init_fov;
	int				prev_fov;
	double			proj_dst;
	double			half_fov_rad;
	double			move_increase;
	int				pitch_max;
	int				map_x;
	int				map_y;
	char			**map;
	char			**floor_map;
	t_ray			*rays;
	mlx_image_t		*image;
	mlx_image_t		*image_death;
	mlx_image_t		*image_menu;
	t_projectile	*projectiles;
	t_vect2			pos;
	t_player		player;
	bool			moving;
	unsigned long	init_t;
	unsigned long	final_t;
	int				fps;
	double			mod_rate;
	int				line_girth;
	double			mouse_sens;
	int				upscaling;
	mlx_texture_t	*texture;
	mlx_texture_t	*texture2;
	mlx_texture_t	*texture3;
	mlx_texture_t	*texture4;
	mlx_texture_t	*texture5;
	mlx_texture_t	*texture6;
	mlx_texture_t	*texture_died;
	mlx_texture_t	*texture_pump;
	mlx_texture_t	*crosshair;
	double			min_length;
	int8_t			*prev_buffer;
	int8_t			*new_buffer;
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
	double			mini_map_size;
	double			mini_map_grid_size;

	double			tilt_angle;
	double			target_angle;
	double			shear_factor;
	double			tilt_addition_height;
	double			tilt_addition_width;

	bool			is_sliding;

	t_menu			menu;

	t_heart			heart;

	t_flash			flash;

	t_blood_explosion	blood_explosion;
	// t_audio			*audio;
}					t_cube;

#endif

bool				ft_check_limits(t_cube *cube, t_vect2 len);
void				ft_limit_cords(t_cube *cube, t_vect2 *len);
t_vect2				hori_first_point(t_cube *cube, t_ray *ray);
t_vect2				vert_first_point(t_cube *cube, t_ray *ray);
void 				ft_updated_res_init(t_cube *cube);
void 				ft_updated_buff_init(t_cube *cube);
void 				ft_draw_line(t_cube *cube, t_vect2 start, t_vect2 finish, int color);
