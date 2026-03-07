#include "../../includes/cub3d.h"

void	ft_menu_2(t_cube *cube, t_vars5 vars, int *x)
{
	vars.tex_x = (double)(vars.x) *vars.ratio_x;
	vars.pixel_cords = (vars.y * 4 * cube->screen_width_buff) + (vars.x * 4);
	vars.title_cords = (vars.tex_y * 4 * vars.texture->width) + (vars.tex_x
			* 4);
	if (vars.tex_x >= vars.texture->width || vars.tex_y >= vars.texture->height
		|| vars.texture->pixels[vars.tex_y * 4 * vars.texture->width
			+ vars.tex_x * 4 + 3] < 127)
		return ((void)(*x)++);
	cube->image->pixels[vars.pixel_cords
		+ 0] = vars.texture->pixels[vars.title_cords + 0];
	cube->image->pixels[vars.pixel_cords
		+ 1] = vars.texture->pixels[vars.title_cords + 1];
	cube->image->pixels[vars.pixel_cords
		+ 2] = vars.texture->pixels[vars.title_cords + 2];
	cube->image->pixels[vars.pixel_cords
		+ 3] = vars.texture->pixels[vars.title_cords + 3];
	(*x)++;
}

void	ft_menu_3(t_cube *cube, t_vars5 vars)
{
	mlx_get_mouse_pos(cube->mlx, &vars.mouse_x, &vars.mouse_y);
	if (cube->menu.state == 1)
	{
		ft_settings(cube);
		if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
			&& ((double)vars.mouse_x > ((double)cube->screen_width_buff
					* 0.0156)
				&& (double)vars.mouse_x < ((double)cube->screen_width_buff
					* 0.0468))
			&& ((double)vars.mouse_y > ((double)cube->screen_height_buff
					* 0.0277))
			&& ((double)vars.mouse_y < (double)cube->screen_height_buff
				* 0.0833))
			cube->menu.state = 0;
		return ;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ENTER))
		cube->state = GAME;
	if (mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& ((double)vars.mouse_x > ((double)cube->screen_width_buff * 0.92)
			&& (double)vars.mouse_x < ((double)cube->screen_width_buff * 0.97))
		&& ((double)vars.mouse_y > ((double)cube->screen_height_buff * 0.85))
		&& ((double)vars.mouse_y < (double)cube->screen_height_buff * 0.95))
		cube->menu.state = 1;
}

void	ft_menu(t_cube *cube)
{
	t_vars5	vars;

	vars.start_x = 0;
	vars.start_y = 0;
	vars.x = vars.start_x;
	vars.y = 0;
	if (cube->menu.state == 0)
		vars.texture = cube->menu.title;
	else
		vars.texture = cube->menu.settings.background;
	vars.ratio_y = ((double)(vars.texture->height)
			/ (double)(cube->screen_height_buff));
	vars.ratio_x = ((double)(vars.texture->width)
			/ (double)(cube->screen_width_buff));
	while (vars.y < cube->screen_height_buff)
	{
		vars.x = vars.start_x;
		vars.tex_y = (double)(vars.y) *vars.ratio_y;
		while (vars.x < cube->screen_width_buff)
			ft_menu_2(cube, vars, &vars.x);
		vars.y++;
	}
	ft_menu_3(cube, vars);
}

void	ft_settings_2(t_cube *cube, int mouse_x, int mouse_y)
{
	if (mouse_y > (cube->menu.settings.fov.slider_start_y)
		&& mouse_y < (cube->menu.settings.fov.slider_end_y)
		&& mouse_x < (cube->menu.settings.fov.slider_end_x)
		&& mouse_x > (cube->menu.settings.fov.slider_start_x))
		cube->menu.settings.mouse_held = FOV_SLIDER;
	else if (mouse_x > cube->menu.settings.res.start_x_1080
		&& mouse_y > cube->menu.settings.res.start_y_1080_900
		&& mouse_x < cube->menu.settings.res.end_x_480
		&& mouse_y < cube->menu.settings.res.end_y_480)
		cube->menu.settings.mouse_held = RESOLUTION;
	else if (mouse_y > (cube->menu.settings.mouse_sens.slider_start_y)
		&& mouse_y < (cube->menu.settings.mouse_sens.slider_end_y)
		&& mouse_x < (cube->menu.settings.mouse_sens.slider_end_x)
		&& mouse_x > (cube->menu.settings.mouse_sens.slider_start_x))
		cube->menu.settings.mouse_held = MOUSE_SENS_SLIDER;
	else if (mouse_x > cube->menu.settings.ups.start_x15
		&& mouse_x < cube->menu.settings.ups.end_x48
		&& mouse_y > cube->menu.settings.ups.start_y1234
		&& mouse_y < cube->menu.settings.ups.end_y5678)
		cube->menu.settings.mouse_held = UPS;
}

void	ft_settings(t_cube *cube)
{
	int	mouse_x;
	int	mouse_y;

	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	if (cube->menu.settings.mouse_held == NOTHING
		&& mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
		ft_settings_2(cube, mouse_x, mouse_y);
	if (cube->menu.settings.mouse_held != NOTHING
		&& !mlx_is_mouse_down(cube->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		cube->menu.settings.mouse_held = NOTHING;
	}
	ft_fov_slider(cube);
	ft_res(cube);
	if (cube->menu.settings.mouse_held == NOTHING
		|| cube->menu.settings.mouse_held == MOUSE_SENS_SLIDER)
		ft_crosshair_color(cube);
	ft_mouse_sens(cube);
	ft_upscale(cube);
}
