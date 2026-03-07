#include "../../includes/cub3d.h"

void	ft_res_1080_900(t_cube *cube, int mouse_x, int mouse_y)
{
	if (mouse_x > cube->menu.settings.res.start_x_1080
		&& mouse_x < cube->menu.settings.res.end_x_1080)
		ft_update_screen_buff(cube, cube->menu.settings.res._1080, 1920, 1080);
	else if (mouse_x > cube->menu.settings.res.start_x_900
		&& mouse_x < cube->menu.settings.res.end_x_900)
		ft_update_screen_buff(cube, cube->menu.settings.res._900, 1600, 900);
}

void	ft_res(t_cube *cube)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	if (cube->menu.settings.mouse_held != RESOLUTION)
		return (ft_renderer(cube, cube->menu.settings.res.texture, 0, 0));
	if (mouse_y > cube->menu.settings.res.start_y_1080_900
		&& mouse_y < cube->menu.settings.res.end_y_1080_900)
		ft_res_1080_900(cube, mouse_x, mouse_y);
	else if (mouse_y > cube->menu.settings.res.start_y_480
		&& mouse_y < cube->menu.settings.res.end_y_480)
	{
		if (mouse_x > cube->menu.settings.res.start_x_720
			&& mouse_x < cube->menu.settings.res.end_x_720)
			ft_update_screen_buff(cube, cube->menu.settings.res._720, 1280,
				720);
		else if (mouse_x > cube->menu.settings.res.start_x_480
			&& mouse_x < cube->menu.settings.res.end_x_480)
			ft_update_screen_buff(cube, cube->menu.settings.res._480, 720, 480);
	}
	ft_renderer(cube, cube->menu.settings.res.texture, 0, 0);
}

void	ft_crosshair_color2(t_cube *cube, t_vars6 *vars)
{
	vars->end_x = vars->start_x + (0.05 * (double)cube->screen_width_buff);
	vars->end_y = vars->start_y + (0.064 * (double)cube->screen_height_buff);
	vars->x = vars->start_x + (0.1 * (vars->end_x - vars->start_x));
	vars->y = vars->start_y + (0.1 * (vars->end_y - vars->start_y));
	vars->color = vars->prev[vars->mouse_y * cube->screen_width_buff
		+ vars->mouse_x];
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		vars->crosshair = (uint32_t *)cube->crosshair->pixels;
		vars->i = 0;
		vars->j = 0;
		while (vars->j < cube->crosshair->height)
		{
			vars->i = 0;
			while (vars->i++ < cube->crosshair->width)
			{
				vars->index = vars->j * cube->crosshair->width + vars->i;
				if (vars->crosshair[vars->index]
					== (uint32_t)cube->menu.settings.crosshair.color)
					vars->crosshair[vars->index] = vars->color;
			}
			vars->j++;
		}
		cube->menu.settings.crosshair.color = vars->color;
	}
}

void	ft_crosshair_color3(t_cube *cube, t_vars6 *vars)
{
	while (vars->y < vars->end_y)
	{
		vars->x = vars->start_x;
		while (vars->x < vars->end_x)
		{
			vars->prev[vars->y * cube->screen_width_buff
				+ vars->x] = vars->color;
			vars->x++;
		}
		vars->y++;
	}
}

void	ft_crosshair_color(t_cube *cube)
{
	t_vars6	vars;

	vars.mouse_x;
	vars.mouse_y;
	vars.prev = (uint32_t *)cube->image->pixels;
	mlx_get_mouse_pos(cube->mlx, &vars.mouse_x, &vars.mouse_y);
	if (vars.mouse_x > cube->menu.settings.crosshair.start_x
		&& vars.mouse_x < cube->menu.settings.crosshair.end_x
		&& vars.mouse_y > cube->menu.settings.crosshair.start_y
		&& vars.mouse_y < cube->menu.settings.crosshair.end_y)
	{
		vars.start_x = vars.mouse_x + (0.01 * (double)cube->screen_width_buff);
		vars.start_y = vars.mouse_y - (0.06 * (double)cube->screen_height_buff);
		ft_crosshair_color2(cube, &vars);
		ft_crosshair_color3(cube, &vars);
		ft_renderer(cube, cube->menu.settings.crosshair.border, vars.start_x,
			vars.start_y);
	}
}
