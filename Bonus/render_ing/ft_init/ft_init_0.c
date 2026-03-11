/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 13:51:25 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 22:55:53 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_0(t_cube *cube, t_nc *nu)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	cube->camera_h = CAM_H;
	cube->dst_camera_h = CAM_H;
	cube->map_x = nu->x;
	cube->map_y = nu->y;
	cube->is_sliding = false;
	cube->ups = UPS_RATE;
	cube->screen_height_buff = SCREEN_HEIGHT_BUFF;
	cube->screen_width_buff = SCREEN_WIDTH_BUFF;
	cube->screen_height = (double)cube->screen_height_buff / (double)cube->ups;
	cube->screen_width = (double)cube->screen_width_buff / (double)cube->ups;
	cube->mini_map_size = 0.2 * cube->screen_width_buff;
	cube->mini_map_grid_size = cube->mini_map_size / GRID_SIZE;
	cube->res = cube->screen_width;
	cube->move_increase = 0.05 * (double)cube->screen_height;
	cube->pitch_max = (double)cube->screen_height * 1.1;
	cube->init_fov = FOV;
	cube->fov = cube->init_fov;
	cube->prev_fov = cube->init_fov;
}

void	ft_init_1(t_cube *cube, t_nc *nu)
{
	cube->mouse_sens = TURN_SPEED;
	cube->proj_dst = ((double)cube->screen_width / 2.0) / tan(((double)cube->fov
				/ 2.0) * RADIANT_RATE);
	cube->half_fov_rad = tan(((double)cube->fov / 2.0) * RADIANT_RATE);
	cube->player.x = (GRID_SIZE * (double)nu->start->x) + GRID_SIZE / 2.0;
	cube->player.y = (GRID_SIZE * (double)nu->start->y) + GRID_SIZE / 2.0;
	cube->player.hp = MAX_HP;
	cube->player.delay = false;
	cube->player.atk_delay = 1;
	cube->player.dmg = 50;
	cube->player.speed_mult = PLAYER_SPEED;
	cube->player.dst_speed_mult = PLAYER_SPEED;
	cube->player.move_state = WALK;
	cube->player.current_speed_lr_x = 0.0;
	cube->player.current_speed_lr_y = 0.0;
	cube->player.current_speed_fb_x = 0.0;
	cube->player.current_speed_fb_y = 0.0;
	cube->player.last_fb = UP;
	cube->player.last_lr = LEFT;
	cube->player.attacked = false;
	cube->player.hit = false;
}

void	ft_init_2(t_cube *cube)
{
	if (cube->nu->start->door == 'E')
		cube->player.angle = 0;
	else if (cube->nu->start->door == 'W')
		cube->player.angle = PI;
	else if (cube->nu->start->door == 'S')
		cube->player.angle = PI / 2.0;
	else if (cube->nu->start->door == 'N')
		cube->player.angle = (PI / 2.0) + PI;
	cube->state = MENU;
	cube->prev_state = MENU;
	ft_load_png(cube, &(cube->menu.title), "./as/menu.png");
	ft_load_png(cube, &(cube->menu.settings.background), "./sa/s_bg.png");
	ft_load_png(cube, &(cube->menu.settings.fov.bar_1), "./sa/bar_1.png");
	ft_load_png(cube, &(cube->menu.settings.bar_2), "./sa/bar_2.png");
	ft_load_png(cube, &(cube->menu.settings.fov.slider_1), "./sa/slider_1.png");
	ft_load_png(cube, &(cube->menu.settings.slider_2), "./sa/slider_2.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x1_glow), "./sa/x1_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x2_glow), "./sa/x2_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x3_glow), "./sa/x3_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x4_glow), "./sa/x4_glow.png");
}

void	ft_init_3(t_cube *cube)
{
	ft_load_png(cube, &(cube->menu.settings.ups.x5_glow), "./sa/x5_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x6_glow), "./sa/x6_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x7_glow), "./sa/x7_glow.png");
	ft_load_png(cube, &(cube->menu.settings.ups.x8_glow), "./sa/x8_glow.png");
	cube->menu.settings.ups.start_x15 = 0.089 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x15 = 0.11 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x26 = 0.162 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x26 = 0.183 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x37 = 0.235 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x37 = 0.256 * cube->screen_width_buff;
	cube->menu.settings.ups.start_x48 = 0.310 * cube->screen_width_buff;
	cube->menu.settings.ups.end_x48 = 0.331 * cube->screen_width_buff;
	cube->menu.settings.ups.start_y1234 = 0.78 * cube->screen_height_buff;
	cube->menu.settings.ups.end_y1234 = 0.807 * cube->screen_height_buff;
	cube->menu.settings.ups.start_y5678 = 0.873 * cube->screen_height_buff;
	cube->menu.settings.ups.end_y5678 = 0.9 * cube->screen_height_buff;
}

void	ft_init_4(t_cube *cube)
{
	if (cube->ups == 1)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x1_glow;
	else if (cube->ups == 2)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x2_glow;
	else if (cube->ups == 3)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x3_glow;
	else if (cube->ups == 4)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x4_glow;
	else if (cube->ups == 5)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x5_glow;
	else if (cube->ups == 6)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x6_glow;
	else if (cube->ups == 7)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x7_glow;
	else if (cube->ups == 8)
		cube->menu.settings.ups.texture = cube->menu.settings.ups.x8_glow;
	cube->menu.settings.mouse_held = 0;
	cube->menu.settings.fov.slider_start_y = 0.20 * cube->screen_height_buff;
	cube->menu.settings.fov.slider_end_y = 0.24 * cube->screen_height_buff;
	cube->menu.settings.fov.slider_start_x = 0.065 * cube->screen_width_buff;
	cube->menu.settings.fov.slider_end_x = 0.354 * cube->screen_width_buff;
	cube->menu.settings.fov.min_fov = 30;
	cube->menu.settings.fov.max_fov = 150;
}
