/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:31 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/11 03:01:03 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_10(t_cube *cube, t_nc *nu)
{
	cube->texture2 = nu->txtrs[SO];
	cube->texture3 = nu->txtrs[WE];
	cube->texture4 = nu->txtrs[EA];
	cube->line_girth = (int)(cube->screen_width / cube->res);
	if (cube->line_girth == 0)
		cube->line_girth = 1;
	cube->mlx = mlx_init(cube->screen_width_buff, cube->screen_height_buff,
			"cub3d", true);
	if (cube->mlx == NULL)
	{
		perror("mlx init error :");
		ft_clean(cube, cube->nu, 1);
	}
	cube->image = mlx_new_image(cube->mlx, cube->screen_width_buff,
			cube->screen_height_buff);
	if (cube->image == NULL)
	{
		mlx_terminate(cube->mlx);
		perror("image init error :");
		ft_clean(cube, cube->nu, 1);
	}
}

void	ft_init_11(t_cube *cube)
{
	cube->image_death = mlx_new_image(cube->mlx, cube->screen_width_buff,
			cube->screen_height_buff);
	if (cube->image_death == NULL)
	{
		mlx_terminate(cube->mlx);
		perror("image init error :");
		ft_clean(cube, cube->nu, 1);
	}
	mlx_image_to_window(cube->mlx, cube->image, 0, 0);
	mlx_set_mouse_pos(cube->mlx, cube->screen_width / 2, cube->screen_height
		/ 2);
}
