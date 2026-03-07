#include "../../includes/cub3d.h"

void	ft_set_values(t_cube *cube, t_vars values)
{
	int	val;
	int	tex_val;

	val = (values.y * 4 * cube->screen_width) + (values.x * 4);
	tex_val = (int)(((int)values.j * cube->texture_died->bytes_per_pixel
				* cube->texture_died->width) + ((int)values.i
				* cube->texture_died->bytes_per_pixel));
	cube->prev_buffer[val] = cube->texture_died->pixels[tex_val + 0];
	cube->prev_buffer[val + 1] = cube->texture_died->pixels[tex_val + 1];
	cube->prev_buffer[val + 2] = cube->texture_died->pixels[tex_val + 2];
	cube->prev_buffer[val + 3] = cube->texture_died->pixels[tex_val + 3];
}

void	ft_died(t_cube *cube, double i, double j)
{
	double	i_iter;
	double	j_iter;

	int (x), (y);
	x = 0;
	y = 0;
	i_iter = (double)cube->texture_died->width / (double)cube->screen_width;
	j_iter = (double)cube->texture_died->height / (double)cube->screen_height;
	while (x < cube->screen_width)
	{
		y = -1;
		j = 0;
		while (y < cube->screen_height)
		{
			if ((int)i >= (int)cube->texture_died->width)
				i = cube->texture_died->width - 1;
			if ((int)j >= (int)cube->texture_died->height)
				j = cube->texture_died->height - 1;
			ft_set_values(cube, (t_vars){x, y, i, j});
			y++;
			j += j_iter;
		}
		i += i_iter;
		x++;
	}
}
