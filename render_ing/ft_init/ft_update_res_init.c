#include "../../includes/cub3d.h"

void	ft_updated_res_init(t_cube *cube)
{
	cube->res = cube->screen_width;
	cube->tilt_addition_height = fabs(cube->shear_factor) * cube->screen_height;
	cube->tilt_addition_width = fabs(cube->shear_factor) * cube->screen_width;
	cube->move_increase = 0.05 * cube->screen_height;
	cube->pitch_max = cube->screen_height + 100;
	free(cube->prev_buffer);
	free(cube->new_buffer);
	free(cube->lerp_buffer);
	free(cube->z_buffer);
	free(cube->rays);
	cube->prev_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	cube->new_buffer = ts_calloc((cube->screen_height
				- cube->tilt_addition_height) * (cube->screen_width
				- cube->tilt_addition_width), 4);
	cube->lerp_buffer = ts_calloc(cube->screen_height * cube->screen_width, 4);
	cube->rays = ts_calloc(cube->res + 1, sizeof(t_ray));
	cube->z_buffer = ts_calloc(cube->screen_width + 1, sizeof(double));
	cube->proj_dst = (cube->screen_width / 2.0) / tan((cube->fov / 2.0)
			* RADIANT_RATE);
	cube->line_girth = (int)(cube->screen_width / cube->res);
	cube->mod_rate = (cube->fov * RADIANT_RATE) / cube->res;
	clear_image(cube);
}
