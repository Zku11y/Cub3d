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
