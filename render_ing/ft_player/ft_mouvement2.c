#include "../../includes/cub3d.h"

void	ft_turn(t_cube *cube)
{
	int			mouse_x;
	int			mouse_y;
	static int	frames;

	frames = 5;
	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	mouse_x = mouse_x - (cube->screen_width / 2);
	mouse_y = mouse_y - (cube->screen_height / 2);
	cube->player.angle += mouse_x * (cube->mouse_sens * 100)
		/ (((double)cube->screen_height / 100)
			* (cube->menu.settings.fov.max_fov - cube->fov
				+ cube->menu.settings.fov.min_fov));
	if (frames > 0)
		frames--;
	else
		cube->pitch += (-1 * mouse_y) * ((cube->mouse_sens * 100));
	if (cube->pitch > cube->pitch_max)
		cube->pitch = cube->pitch_max;
	if (cube->pitch < -cube->pitch_max)
		cube->pitch = -cube->pitch_max;
	mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height
		/ 2);
}
