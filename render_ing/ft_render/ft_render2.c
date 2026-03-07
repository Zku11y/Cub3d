#include "../../includes/cub3d.h"

void	ft_ups2(t_cube *cube, t_vars8 *vars, mlx_image_t *image)
{
	if (cube->state == GAME)
	{
		vars->prev = (uint32_t *)cube->new_buffer;
		vars->screen_H = cube->screen_height - (cube->tilt_addition_height * 2);
		vars->screen_W = cube->screen_width - (cube->tilt_addition_width * 2);
	}
	vars->iter_x = (double)vars->screen_W / (double)cube->screen_width_buff;
	vars->iter_y = (double)vars->screen_H / (double)cube->screen_height_buff;
	vars->prev_x = 0.0;
	vars->prev_y = 0.0;
	vars->new_x = 0;
	vars->new_y = 0;
}

void	ft_ups(t_cube *cube, mlx_image_t *image)
{
	t_vars8	vars;

	vars.new = (uint32_t *)image->pixels;
	vars.prev = (uint32_t *)cube->prev_buffer;
	vars.screen_H = cube->screen_height;
	vars.screen_W = cube->screen_width;
	ft_ups2(cube, &vars, image);
	while (vars.new_y < cube->screen_height_buff && vars.prev_y < vars.screen_H)
	{
		vars.new_x = 0;
		vars.prev_x = 0.0;
		while (vars.new_x < cube->screen_width_buff
			&& vars.prev_x < vars.screen_W)
		{
			vars.new[(vars.new_y * cube->screen_width_buff)
				+ vars.new_x] = vars.prev[((int)vars.prev_y * vars.screen_W)
				+ (int)vars.prev_x];
			vars.new_x++;
			vars.prev_x += vars.iter_x;
		}
		vars.new_y++;
		vars.prev_y += vars.iter_y;
	}
}
