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
