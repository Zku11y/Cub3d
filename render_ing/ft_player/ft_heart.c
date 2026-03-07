#include "../../includes/cub3d.h"

void	ft_heart(t_cube *cube)
{
	if ((double)cube->player.HP > (0.8 * (double)MAX_HP))
		return ((void)(cube->heart.blur_lerp = BLUR_LERP));
	else if ((double)cube->player.HP > (0.6 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.8 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_1, 0, 0);
		cube->heart.blur_lerp = 0.4;
	}
	else if ((double)cube->player.HP > (0.4 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.6 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_2, 0, 0);
		cube->heart.blur_lerp = 0.3;
	}
	else if ((double)cube->player.HP > (0.2 * (double)MAX_HP)
		&& (double)cube->player.HP <= (0.4 * (double)MAX_HP))
	{
		ft_prev_renderer(cube, cube->heart.frame_3, 0, 0);
		cube->heart.blur_lerp = 0.2;
	}
	else
	{
		ft_prev_renderer(cube, cube->heart.frame_4, 0, 0);
		cube->heart.blur_lerp = 0.1;
	}
}

bool	ft_health2(t_cube *cube, mlx_texture_t *texture, t_enemy *enemy,
		t_vars10 *vars)
{
	if (vars->player_dst < HITBOX_DST)
	{
		cube->flash.r = 0.2;
		cube->flash.g = 3.0;
		cube->flash.b = 0.2;
		cube->player.HP += 50;
		if (cube->player.HP > MAX_HP)
			cube->player.HP = MAX_HP;
		return (enemy->health_spawn = false, false);
	}
	vars->angle_diff = atan2(vars->pos_y - cube->player.y, vars->pos_x
			- cube->player.x);
	vars->tetha_delta = vars->angle_diff - cube->player.angle;
	while (vars->tetha_delta > PI)
		vars->tetha_delta -= 2 * PI;
	while (vars->tetha_delta < -PI)
		vars->tetha_delta += 2 * PI;
	vars->midX = ((0.5 * cube->screen_width)) + (tan(vars->tetha_delta)
			* cube->proj_dst);
	vars->dst = sqrt((vars->pos_x - cube->player.x) * (vars->pos_x
				- cube->player.x) + (vars->pos_y - cube->player.y)
			* (vars->pos_y - cube->player.y)) * cos(vars->tetha_delta);
	if (vars->dst < 0.1)
		return (false);
	return (true);
}

void	ft_health3(t_cube *cube, mlx_texture_t *texture, t_enemy *enemy,
		t_vars10 *vars)
{
	vars->tmp = 1.0 - (vars->dst / MAX_DST);
	if (vars->tmp > 1.0)
		vars->tmp = 1.0;
	else if (vars->tmp < 0.0)
		vars->tmp = 0.0;
	vars->height = (GRID_SIZE / vars->dst) * cube->proj_dst;
	vars->scale_ratio = texture->height / vars->height;
	vars->proj_z_offset = (((GRID_SIZE / 2.0) - cube->camera_h) / vars->dst)
		* cube->proj_dst;
	vars->start_x = vars->midX - (texture->width / vars->scale_ratio) / 2;
	vars->start_y = ((cube->screen_height / 2.0) + cube->pitch
			+ enemy->health_offset - vars->proj_z_offset) - (texture->height
			/ vars->scale_ratio) / 2;
	vars->const_y = vars->start_y;
	vars->end_x = vars->start_x + (texture->width / vars->scale_ratio);
	vars->end_y = vars->start_y + (texture->height / vars->scale_ratio);
	vars->tex_x = 0;
	vars->tex_y = 0;
	if (vars->start_x < 0)
	{
		vars->tex_x += (-vars->start_x) * vars->scale_ratio;
		vars->start_x = 0;
	}
}
