#include "../../includes/cub3d.h"

void ft_update_screen_res(t_cube *cube, int upscale, mlx_texture_t *texture){
    if(upscale == cube->ups)
        return;
    cube->menu.settings.ups.texture = texture;
    cube->ups = upscale;
    cube->screen_height = cube->screen_height_buff / cube->ups;
    cube->screen_width = cube->screen_width_buff / cube->ups;
    ft_updated_res_init(cube);
}

void	ft_upscale2(t_cube *cube, int mouse_x)
{
	if (mouse_x > cube->menu.settings.ups.start_x15
		&& mouse_x < cube->menu.settings.ups.end_x15)
		ft_update_screen_res(cube, 1, cube->menu.settings.ups.x1_glow);
	else if (mouse_x > cube->menu.settings.ups.start_x26
		&& mouse_x < cube->menu.settings.ups.end_x26)
		ft_update_screen_res(cube, 2, cube->menu.settings.ups.x2_glow);
	else if (mouse_x > cube->menu.settings.ups.start_x37
		&& mouse_x < cube->menu.settings.ups.end_x37)
		ft_update_screen_res(cube, 3, cube->menu.settings.ups.x3_glow);
	else if (mouse_x > cube->menu.settings.ups.start_x48
		&& mouse_x < cube->menu.settings.ups.end_x48)
		ft_update_screen_res(cube, 4, cube->menu.settings.ups.x4_glow);
}

void	ft_upscale(t_cube *cube)
{
	int (mouse_x), (mouse_y);
	mlx_get_mouse_pos(cube->mlx, &mouse_x, &mouse_y);
	if (cube->menu.settings.mouse_held != UPS)
		return (ft_renderer(cube, cube->menu.settings.ups.texture, 0, 0));
	if (mouse_y > cube->menu.settings.ups.start_y1234
		&& mouse_y < cube->menu.settings.ups.end_y1234)
		ft_upscale2(cube, mouse_x);
	else if (mouse_y > cube->menu.settings.ups.start_y5678
		&& mouse_y < cube->menu.settings.ups.end_y5678)
	{
		if (mouse_x > cube->menu.settings.ups.start_x15
			&& mouse_x < cube->menu.settings.ups.end_x15)
			ft_update_screen_res(cube, 5, cube->menu.settings.ups.x5_glow);
		else if (mouse_x > cube->menu.settings.ups.start_x26
			&& mouse_x < cube->menu.settings.ups.end_x26)
			ft_update_screen_res(cube, 6, cube->menu.settings.ups.x6_glow);
		else if (mouse_x > cube->menu.settings.ups.start_x37
			&& mouse_x < cube->menu.settings.ups.end_x37)
			ft_update_screen_res(cube, 7, cube->menu.settings.ups.x7_glow);
		else if (mouse_x > cube->menu.settings.ups.start_x48
			&& mouse_x < cube->menu.settings.ups.end_x48)
			ft_update_screen_res(cube, 8, cube->menu.settings.ups.x8_glow);
	}
	ft_renderer(cube, cube->menu.settings.ups.texture, 0, 0);
}
