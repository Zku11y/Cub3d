/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:13:48 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 14:13:49 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_map_entity1(t_cube *cube, t_vars14 *vars, double pos_x,
		double pos_y)
{
	vars->offset = 5;
	vars->x = pos_x - vars->offset;
	while (vars->x < (pos_x + vars->offset))
	{
		vars->y = pos_y - vars->offset;
		while (vars->y < (pos_y + vars->offset))
		{
			vars->dst = sqrt(((double)vars->y - pos_y) * ((double)vars->y
						- pos_y) + ((double)vars->x - pos_x) * ((double)vars->x
						- pos_x));
			if (vars->dst < (double)vars->offset)
				mlx_put_pixel(cube->image, vars->x, vars->y, 0xff1100ff);
			vars->y++;
		}
		vars->x++;
	}
}

void	draw_map_entity(t_cube *cube, double pos_x, double pos_y, double angle)
{
	t_vars14	vars;

	draw_map_entity1(cube, &vars, pos_x, pos_y);
	vars.arrow_start_x = pos_x + cos(angle) * 13;
	vars.arrow_start_y = pos_y + sin(angle) * 13;
	vars.arrow_angle = PI / 4;
	vars.left_x = vars.arrow_start_x - (cos(angle - vars.arrow_angle) * 9);
	vars.left_y = vars.arrow_start_y - (sin(angle - vars.arrow_angle) * 9);
	vars.right_x = vars.arrow_start_x - (cos(angle + vars.arrow_angle) * 9);
	vars.right_y = vars.arrow_start_y - (sin(angle + vars.arrow_angle) * 9);
	ft_draw_line(cube, (t_vect2){vars.arrow_start_x, vars.arrow_start_y, 0, 0},
		(t_vect2){vars.left_x, vars.left_y, 0, 0}, 0xff1100ff);
	ft_draw_line(cube, (t_vect2){vars.arrow_start_x, vars.arrow_start_y, 0, 0},
		(t_vect2){vars.right_x, vars.right_y, 0, 0}, 0xff1100ff);
}

void	draw_player(t_cube *cube)
{
	draw_map_entity(cube, cube->mini_map_size / 2, cube->mini_map_size / 2,
		cube->player.angle);
}
