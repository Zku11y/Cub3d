/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:15:11 by skully            #+#    #+#             */
/*   Updated: 2026/03/11 02:01:48 by mdakni           ###   ########.fr       */
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

//-----------------------------------------------------------------

#include "../pars_ing/libts/libts.h"

typedef enum e_key
{

	WA,
	FL,
	CI,
	PR,
	EN,
	ED,
	HP
}	t_key;

typedef struct s_elv
{
	int			x;
	int			y;
	int			d_x;
	int			d_y;
	char		who;
	char		door;
}				t_elv;

typedef struct s_mp
{
	char			*val;
	struct s_mp		*next;
}					t_mp;

typedef struct s_teto
{
	char			*val;
	struct s_teto	*next;
	t_key			key;
}					t_teto;

typedef struct s_nc
{
	char			*imgs[7];
	mlx_texture_t	*txtrs[7];
	struct s_nc		*next;
	char			**map;
	t_elv			*start;
	t_elv			*end;
	int				x;
	int				y;
}					t_nc;

void		ts_cln_pngs(t_nc *nu);
int			ts_spaces_skip(char *str);
char		*ts_get_val(char *str);
t_teto		*ts_key(char *lain);
int			ts_mt(char *lain);
char		*get_lain(int fd);
t_teto		*ts_read(int fd);
int			ts_check_data(t_nc *nu);
void		ts_free_pear(t_teto *head);
int			ts_opn(char *path);
int			dot_chk(char *path);
void		ts_free_one_nomap(t_nc *nu);
t_nc		*ts_put(t_teto *teto); 
void		free_nu_map(char **nu);
int			get_map(int fd, t_nc *nu);
int			rec_map(char **map, t_nc *nu);
t_nc		*ts_pars(char **arg);
void		free_nu(t_nc *nu);
t_nc		*ts_make_one(int fd);
void		free_mp(t_mp *mp);
void		map_cln(char **map, int x, int y, t_elv *hi);
void		put_door(char **map, t_elv *hi);
int			ts_check_door(char **map, int x, int y);
int			ts_check_elv(char **map);
int			get_path(char **map, t_elv *elv, int *m_s);
t_elv		*get_elv(char **map, char who);
int			chk_elv(char **map);
int			get_door(char **map, t_elv *hi);
int			ts_edg_chk(char **map, int m_x, int m_y);
char		*get_lain_with_space(int fd);

//-----------------------------------------------------------------

# define UPS_RATE 4
# define SCREEN_WIDTH_BUFF 1920
# define SCREEN_HEIGHT_BUFF 1080
# define SCREEN_WIDTH (SCREEN_WIDTH_BUFF / UPS_RATE)
# define SCREEN_HEIGHT (SCREEN_HEIGHT_BUFF / UPS_RATE)
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
# define ENEMY_NUM 15
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

typedef struct s_vars
{
	int			x;
	int			y;
	double				i;
	double				j;
}					t_vars;

typedef struct s_vars2
{
	int			*x;
	int			*y;
	int			*start_x;
	int			*start_y;
	int			*tex_x;
	int			*tex_y;
	int			*prev_cords;
	int			*weapon_cords;
}					t_vars2;

typedef struct s_vars3
{
	int			x;
	int			y;
	int			start_x;
	int			start_y;
	int			tex_x;
	int			tex_y;
	int			prev_cords;
	int			weapon_cords;
	long		current_time;
}					t_vars3;

typedef struct s_vars4
{

    int x;
    int y;
    int max_new_x;
    int max_new_y;
    double prev_x;
    double prev_y;
    double offset;
    struct timeval tv;
    long time; 

}					t_vars4;

typedef struct s_vars5
{

	int				start_x;
	int				start_y;
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	mlx_texture_t	*texture;
	double			ratio_y;
	double			ratio_x;
	int				pixel_cords;
	int				title_cords;
	int				mouse_x;
	int				mouse_y;

}					t_vars5;

typedef struct s_vars6
{

	int				 mouse_x;
	int				 mouse_y;
	int				 start_x;
	int				 start_y;
	int				 end_x;
	int				 end_y;
	int				 x;
	int				 y;
	int				 color;
	int				 i;
	int				 j;
	int				 index;
	uint32_t		 *crosshair;
	uint32_t		 *prev;

}					t_vars6;

typedef struct s_vars7
{
	int			x;
	int			y;
	int			tex_x;
	int			tex_y;
	int			pixel_cords;
	int			title_cords;
	mlx_texture_t *texture;

}					t_vars7;

typedef struct s_vars8
{

	uint32_t	*new;
	uint32_t	*prev;
	int			screen_H;
	int			screen_W;
	double		iter_x;
	double		iter_y;
	double		prev_x;
	double		prev_y;
	int			new_x;
	int			new_y;

}					t_vars8;

typedef struct s_vars9
{

	double			DirX;
	double			DirY;
	double			PlaneX;
	double			PlaneY;
	t_vect2			RayDirL;
	t_vect2			RayDirR;
	double			mid_point;
	double			cam_height;
	double			p;
	mlx_texture_t	*tex;
	int				i;
	double			rowDst;
	t_vect2			floorL;
	t_vect2			floorR;
	t_vect2			step;
	t_vect2			ft_floor;
	double			tmp;
	int				j;
	double			fracX;
	double			fracY;
	int				texX;
	int				texY;
	int				k;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	int				y_iter;
	t_vect2			coords;
	int				iter;


}					t_vars9;

typedef struct s_vars10
{

	struct timeval	tv;
	long			current_time;
	t_vect2			player_dir;
	double			player_dst;
	double			angle_diff;
	double			tetha_delta;
	int				midX;
	double			dst;
	double			tmp;
	double			height;
	double			scale_ratio;
	double			proj_z_offset;
	int				start_x;
	int				start_y;
	int				const_y;
	int				end_x;
	int				end_y;
	int				pos_x;
	int				pos_y;
	double			tex_x;
	double			tex_y;
	int				x;
	int				y;
	int				k;	

}					t_vars10;

typedef struct s_vars11
{

	mlx_texture_t *texture;
	t_vect2	ratio;
	t_vect2	cords;
	t_vect2	start;
	t_vect2	end;
	double	len;
	double	tmp;
	int		k;

}					t_vars11;

typedef struct s_vars12
{

	double DirX;
	double DirY;
	double PlaneX;
	double PlaneY;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double rayAngle;
	int i;	

}					t_vars12;


typedef struct s_vars13
{

	int				 start_x;
	int				 start_y;
	int				 end_x;
	int				 end_y;
	int				 x;
	int				 y;
	int				 i;
	int				 j;
	double		 	 dst;

}					t_vars13;

typedef struct s_vars14
{

	int		y;
	int		x;
	int		offset;
	double	dst;
	int		arrow_start_x;
	int		arrow_start_y;
	double	arrow_angle;
	int		left_x;
	int		left_y;
	int		right_x;
	int		right_y;

	
}					t_vars14;

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
	char			vert_obstacle;
	char			hori_obstacle;
	mlx_texture_t	*texture;
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

typedef struct s_blood
{
	mlx_texture_t **frame;

} t_blood;

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

typedef struct s_res{

	mlx_texture_t	*texture;
	mlx_texture_t	*_480;
	mlx_texture_t	*_720;
	mlx_texture_t	*_900;
	mlx_texture_t	*_1080;
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
    int start_y_480;
    int end_y_480;

}					t_res;

typedef struct s_ups{

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
}					t_ups;

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
	UPS,
	CROSSHAIR,
	MOUSE_SENS_SLIDER
}	t_held;

typedef struct s_settings{

	mlx_texture_t	*background;
	mlx_texture_t	*bar_2;
	mlx_texture_t	*slider_2;
	t_held			mouse_held;
	t_fov			fov;
	t_res	res;
	t_crosshair		crosshair;
	t_mouse_sens	mouse_sens;
	t_ups		ups;

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

	t_nc			*nu;
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
	int				ups;
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

	int				transition;
	int				trans_dst;

	bool			is_sliding;

	t_menu			menu;

	t_heart			heart;

	t_flash			flash;

	t_blood	blood;
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
void				set_screen_buff_limits(t_cube *cube, t_vect2 *len);

void				ft_init_0(t_cube *cube, t_nc *nu);
void				ft_init_1(t_cube *cube, t_nc *nu);
void				ft_init_2(t_cube *cube, t_nc *nu);
void				ft_init_3(t_cube *cube);
void				ft_init_4(t_cube *cube);
void				ft_init_5(t_cube *cube);
void				ft_init_6(t_cube *cube);
void				ft_init_7(t_cube *cube);
void				ft_init_8(t_cube *cube);
void				ft_init_9(t_cube *cube, t_nc *nu);
void				ft_init_10(t_cube *cube, t_nc *nu);
void				ft_init_11(t_cube *cube);

void				ft_updated_buff_init(t_cube *cube);
void				ft_updated_res_init(t_cube *cube);
void				clear_image(t_cube *cube);


void 				ft_init_enemies(t_cube *cube);
unsigned long		ft_rand(unsigned long *seed);
void				ft_map_init(t_cube *cube, t_nc *nu);
void				state_machine(t_cube *cube);
void				state_transition(t_cube *cube, t_state dest);
void 				ft_game(t_cube *cube);
void				ft_mouvement(t_cube *cube, double max_cos_speed, double	max_sin_speed, struct timeval tv);
void    			ft_draw_rays(t_cube *cube);
void    			ft_floor_ceiling(t_cube *cube);
void    			ft_draw_world(t_cube *cube);
void    			ft_draw_enemies(t_cube *cube);
void    			ft_draw_proj(t_cube *cube);
void    			ft_weapon(t_cube *cube);
void    			ft_heart(t_cube *cube);
void    			ft_fov_mod(t_cube *cube);
uint8_t 			ft_lerp_pixels(uint8_t new, uint8_t old, double lerp_rate);
double 				ft_lerp_speed(double dst, double current);
double 				ft_lerp_tilt(double dst, double current);
double				ft_lerp_fov(double dst, double current, double lerp_rate);
double 				ft_lerp_move(double dst, double current, double lerp_rate);
void				ft_died(t_cube *cube, double i, double j);
void				ft_menu(t_cube *cube);
void				ft_tilt(t_cube *cube);
void    			ft_draw_rays(t_cube *cube);
void    			ft_floor_ceiling(t_cube *cube);
void    			ft_draw_world(t_cube *cube);
void    			ft_draw_enemies(t_cube *cube);
void    			ft_draw_proj(t_cube *cube);
void			    ft_weapon(t_cube *cube);
void			    ft_heart(t_cube *cube);
void			    ft_fov_mod(t_cube *cube);
void 				ft_ups(t_cube *cube, mlx_image_t *image);
void				draw_crosshair(t_cube *cube);
void				draw_grid(t_cube *cube);
void				draw_player(t_cube *cube);
void				ft_weapon(t_cube *cube);
void 				ft_prev_renderer(t_cube *cube, mlx_texture_t *texture, int start_x, int start_y);
void				ft_heart(t_cube *cube);
void				ft_tilt(t_cube *cube);
void				ft_draw_proj(t_cube *cube);
bool 				is_looking(t_cube *cube, t_enemy *enemy);
void 				ft_enemy(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture);
void 				ft_projectile(t_cube *cube, t_projectile *projectile);
void				ft_settings(t_cube *cube);
void				ft_crosshair_color(t_cube *cube);
void				ft_fov_slider(t_cube *cube);
void				ft_res(t_cube *cube);
void				ft_mouse_sens(t_cube *cube);
void				ft_upscale(t_cube *cube);
void 				ft_update_screen_res(t_cube *cube, int upscale, mlx_texture_t *texture);
void 				ft_renderer(t_cube *cube, mlx_texture_t *texture, int start_x, int start_y);
void				ft_update_screen_buff(t_cube *cube, mlx_texture_t *texture, int new_w, int new_h);
void				ft_floor_ceiling(t_cube *cube);
bool 				check_screen_limits(t_cube *cube, t_vect2 len);
void 				ft_health(t_cube *cube, t_enemy *enemy);
void 				ft_init_projectile(t_cube *cube, t_enemy *enemy, t_vect2 *dir);
void				ft_enemy6(t_cube *cube, mlx_texture_t *texture, t_vars10 *vars);
void				ft_enemy7(t_cube *cube, mlx_texture_t *texture, t_vars10 *vars);
bool				ft_health2(t_cube *cube, t_enemy *enemy, t_vars10 *vars);
void				ft_health3(t_cube *cube, mlx_texture_t *texture, t_enemy *enemy, t_vars10 *vars);
bool				ft_projectile2(t_cube *cube, t_projectile *projectile, t_vars10 *vars);
bool				ft_projectile3(t_cube *cube, t_projectile *projectile, t_vars10 *vars);
bool				ft_projectile4(t_cube *cube, t_projectile *projectile, t_vars10 *vars);
void				ft_projectile6(t_cube *cube, t_projectile *projectile, t_vars10 *vars);
void				ft_draw_texture(t_cube *cube, t_ray *ray, t_vect2 start, t_vect2 end);
void 				ft_rectangle(t_cube *cube, t_vect2 start_cords, t_vect2 end_cords, int color);
void 				set_screen_limits(t_cube *cube, t_vect2 *len);
t_vect2 			calc_length(t_cube *cube, t_vect2 hori, t_vect2 vert, t_ray *ray);
void				ft_ray_init(t_cube *cube, t_ray *ray, double angle);
void				ft_mouvement1(t_cube *cube);
void				ft_mouvement2(t_cube *cube);
void				ft_turn(t_cube *cube);
void 				ft_angle_limit(double *angle);
void 				ft_mouvement_limits(t_cube *cube, double new_x, double new_y);
void				draw_bg(t_cube *cube, int x, int y, uint32_t color);
void				draw_map_entity(t_cube *cube, double pos_x, double pos_y, double angle);
bool 				check_collision(t_cube *cube, t_vect2 *cords, bool hori_vert, t_ray *ray);
double				ft_safe_tan(double angle);
void				vert_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray, double add);
void				hori_check_next_point(t_cube *cube, t_vect2 *start, t_ray *ray, double add);
void 				ft_clean(t_cube *cube, t_nc *nu, int flag);
void 				ft_load_png(t_cube *cube, mlx_texture_t **tex_buff, char *path);
void				ft_projectile51(t_cube *cube, t_projectile *projectile, t_vars10 *vars);
void				ft_menu31(t_cube *cube, t_vars5 vars);
void				calc_length1(t_cube *cube, double len_vert, t_vect2 vert, t_ray *ray);