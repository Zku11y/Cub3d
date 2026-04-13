/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:12 by mdakni            #+#    #+#             */
/*   Updated: 2026/04/12 22:31:00 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_5(t_cube *cube)
{
	ft_load_png(cube, &(cube->menu.settings.mouse_sens.slider_2),
		"./sa/slider_2.png");
	cube->menu.settings.mouse_sens.slider_start_y = 0.78
		* cube->screen_height_buff;
	cube->menu.settings.mouse_sens.slider_end_y = 0.81
		* cube->screen_height_buff;
	cube->menu.settings.mouse_sens.slider_start_x = 0.605
		* cube->screen_width_buff;
	cube->menu.settings.mouse_sens.slider_end_x = 0.895
		* cube->screen_width_buff;
	cube->menu.settings.mouse_sens.min_sens = 0.0002;
	cube->menu.settings.mouse_sens.max_sens = 0.0040;
	ft_load_png(cube, &(cube->menu.settings.res._480), "./sa/480_glow.png");
	ft_load_png(cube, &(cube->menu.settings.res._720), "./sa/720_glow.png");
	ft_load_png(cube, &(cube->menu.settings.res._900), "./sa/900_glow.png");
	ft_load_png(cube, &(cube->menu.settings.res._1080), "./sa/1080_glow.png");
	if (cube->screen_height_buff == 1080)
		cube->menu.settings.res.texture = cube->menu.settings.res._1080;
	if (cube->screen_height_buff == 900)
		cube->menu.settings.res.texture = cube->menu.settings.res._900;
	if (cube->screen_height_buff == 720)
		cube->menu.settings.res.texture = cube->menu.settings.res._720;
	if (cube->screen_height_buff == 480)
		cube->menu.settings.res.texture = cube->menu.settings.res._480;
}

void	ft_init_61(t_cube *cube)
{
	ft_load_png(cube, &(cube->menu.settings.crosshair.border),
		"./sa/border.png");
	cube->menu.settings.crosshair.color = CROSSHAIR_COLOR;
	cube->menu.settings.crosshair.start_x = 0.636 * cube->screen_width_buff;
	cube->menu.settings.crosshair.end_x = 0.865 * cube->screen_width_buff;
	cube->menu.settings.crosshair.start_y = 0.178 * cube->screen_height_buff;
	cube->menu.settings.crosshair.end_y = 0.58 * cube->screen_height_buff;
	cube->menu.state = 0;
	cube->tilt_angle = 0.0;
	cube->target_angle = 0.0;
	cube->shear_factor = tan(cube->tilt_angle * RADIANT_RATE);
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
}

void	ft_init_6(t_cube *cube)
{
	cube->menu.settings.res.start_x_1080 = 0.055 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_1080 = 0.175 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_900 = 0.245 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_900 = 0.358 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_720 = 0.057 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_720 = 0.173 * cube->screen_width_buff;
	cube->menu.settings.res.start_x_480 = 0.265 * cube->screen_width_buff;
	cube->menu.settings.res.end_x_480 = 0.365 * cube->screen_width_buff;
	cube->menu.settings.res.start_y_1080_900 = 0.48 * cube->screen_height_buff;
	cube->menu.settings.res.end_y_1080_900 = 0.51 * cube->screen_height_buff;
	cube->menu.settings.res.start_y_480 = 0.59 * cube->screen_height_buff;
	cube->menu.settings.res.end_y_480 = 0.62 * cube->screen_height_buff;
	ft_init_61(cube);
}

void	ft_init_7(t_cube *cube)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	cube->player.weapon.dmg = 50;
	cube->player.weapon.fire_rate = 2;
	ft_load_png(cube, &(cube->player.weapon.idle_texture), "./as/dogshit_gun_1.png");
	ft_load_png(cube, &(cube->player.weapon.shoot_texture), "./as/shoot.png");
	ft_load_png(cube, &(cube->player.weapon.pump_texture), "./as/pump.png");
	cube->player.weapon.texture = cube->player.weapon.idle_texture;
	cube->player.weapon.pitch_increase = 1;
	cube->player.weapon.pitch_increased = 0;
	cube->player.weapon.idle_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	cube->player.weapon.idle_frame = 0;
	cube->player.weapon.move_lerp = 0;
	cube->player.weapon.pitch_changed = false;
	ft_load_png(cube, &(cube->heart.frame_1), "./blood/blood_lvl_1.png");
	ft_load_png(cube, &(cube->heart.frame_2), "./blood/blood_lvl_2.png");
	ft_load_png(cube, &(cube->heart.frame_3), "./blood/blood_lvl_3.png");
	ft_load_png(cube, &(cube->heart.frame_4), "./blood/blood_lvl_4.png");
	cube->heart.prev_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (cube->heart.frame = 0, cube->heart.last_angle = 0,
		cube->heart.last_pitch = 0, (void)(cube->heart.added_angle = 0));
}

void	ft_init_8(t_cube *cube)
{
	cube->heart.added_pitch = 0;
	cube->heart.blur_lerp = BLUR_LERP;
	cube->heart.blood_op = 0.0;
	cube->blood.frame = ts_calloc(sizeof(mlx_texture_t *), 13);
	if (!cube->blood.frame)
		return (ft_clean(cube, cube->nu, 1));
	ft_load_png(cube, &(cube->blood.frame[0]), "./blood/1_0.png");
	ft_load_png(cube, &(cube->blood.frame[1]), "./blood/1_1.png");
	ft_load_png(cube, &(cube->blood.frame[2]), "./blood/1_2.png");
	ft_load_png(cube, &(cube->blood.frame[3]), "./blood/1_3.png");
	ft_load_png(cube, &(cube->blood.frame[4]), "./blood/1_4.png");
	ft_load_png(cube, &(cube->blood.frame[5]), "./blood/1_5.png");
	ft_load_png(cube, &(cube->blood.frame[6]), "./blood/1_6.png");
	ft_load_png(cube, &(cube->blood.frame[7]), "./blood/1_7.png");
	ft_load_png(cube, &(cube->blood.frame[8]), "./blood/1_8.png");
	ft_load_png(cube, &(cube->blood.frame[9]), "./blood/1_9.png");
	ft_load_png(cube, &(cube->blood.frame[10]), "./blood/1_10.png");
	ft_load_png(cube, &(cube->blood.frame[11]), "./blood/1_11.png");
	cube->flash.r = 1.0;
	cube->flash.g = 1.0;
	cube->flash.b = 1.0;
	cube->flash.dst_r = 1.0;
	cube->flash.dst_g = 1.0;
	cube->flash.dst_b = 1.0;
	cube->flash.flashed = false;
}
