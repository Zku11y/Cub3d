#include "../../includes/cub3d.h"

void	ft_enemy6(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture,
		t_vars10 *vars)
{
	if (vars->y < 0)
		vars->y = 0;
	if (!check_screen_limits(cube, (t_vect2){vars->start_x, vars->start_y, 0,
			0}))
	{
		vars->k = (vars->x * texture->bytes_per_pixel) + (texture->width
				* texture->bytes_per_pixel * vars->y);
		if (texture->pixels[vars->k + 3] > 128)
		{
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 0] = texture->pixels[vars->k + 0]
				* vars->tmp;
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 1] = texture->pixels[vars->k + 1]
				* vars->tmp;
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 2] = texture->pixels[vars->k + 2]
				* vars->tmp;
			cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
				+ ((int)vars->start_x * 4) + 3] = texture->pixels[vars->k + 3];
		}
	}
	vars->start_y++;
}

void	ft_enemy7(t_cube *cube, t_enemy *enemy, mlx_texture_t *texture,
		t_vars10 *vars)
{
	while (vars->start_x < vars->end_x)
	{
		vars->start_y = vars->const_y;
		vars->x = (int)vars->tex_x;
		if (vars->x >= (int)texture->width)
			vars->x = texture->width - 1;
		if (vars->x < 0)
			vars->x = 0;
		vars->tex_y = 0;
		if (cube->z_buffer[vars->start_x] > vars->dst)
		{
			cube->z_buffer[vars->start_x] = vars->dst;
			while (vars->start_y < vars->end_y)
			{
				vars->y = (int)vars->tex_y;
				if (vars->y >= (int)texture->height)
					vars->y = texture->height - 1;
				ft_enemy6(cube, enemy, texture, vars);
				vars->tex_y += vars->scale_ratio;
			}
		}
		vars->tex_x += vars->scale_ratio;
		vars->start_x++;
	}
}