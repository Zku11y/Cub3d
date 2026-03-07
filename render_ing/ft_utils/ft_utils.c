#include "../../includes/cub3d.h"

void	ft_fov_mod(t_cube *cube)
{
	int	dst_fov;

	if (cube->fov != cube->prev_fov)
	{
		cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0)
				* RADIANT_RATE);
		cube->half_fov_rad = tan((cube->fov / 2.0) * RADIANT_RATE);
		cube->prev_fov = cube->fov;
		cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
	}
	if (cube->player.move_state == WALK)
		cube->fov = ft_lerp_fov(cube->init_fov, cube->fov, FOV_LERP);
	else
	{
		dst_fov = 1.5 * cube->init_fov;
		if (dst_fov > 170)
			dst_fov = 170;
		cube->fov = ft_lerp_fov(dst_fov, cube->fov, 0.04);
	}
}

void	draw_crosshair2(t_cube *cube, t_vars7 *vars)
{
	while (++(vars->x) < cube->screen_width_buff)
	{
		vars->tex_x = (double)(vars->x) * ((double)(cube->crosshair->width)
				/ (double)(cube->screen_width_buff));
		vars->pixel_cords = ((vars->y) * 4 * cube->screen_width_buff)
			+ ((vars->x) * 4);
		vars->title_cords = (vars->tex_y * 4 * cube->crosshair->width)
			+ (vars->tex_x * 4);
		if (vars->tex_x >= cube->crosshair->width
			|| vars->tex_y >= cube->crosshair->height
			|| cube->crosshair->pixels[vars->tex_y * 4 * cube->crosshair->width
				+ vars->tex_x * 4 + 3] < 127)
			continue ;
		cube->image->pixels[vars->pixel_cords
			+ 0] = cube->crosshair->pixels[vars->title_cords + 0];
		cube->image->pixels[vars->pixel_cords
			+ 1] = cube->crosshair->pixels[vars->title_cords + 1];
		cube->image->pixels[vars->pixel_cords
			+ 2] = cube->crosshair->pixels[vars->title_cords + 2];
		cube->image->pixels[vars->pixel_cords
			+ 3] = cube->crosshair->pixels[vars->title_cords + 3];
	}
}

void	draw_crosshair(t_cube *cube)
{
	t_vars7	vars;

	vars.x = 0;
	vars.y = 0;
	while (vars.y < cube->screen_height_buff)
	{
		vars.x = -1;
		vars.tex_y = (double)(vars.y) *((double)(cube->crosshair->height)
				/ (double)(cube->screen_height_buff));
		draw_crosshair2(cube, &vars);
		vars.y++;
	}
}
