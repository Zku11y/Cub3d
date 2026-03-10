/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enemy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:55 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 00:57:14 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	sk_order_enemies(t_cube *cube)
{
	t_enemy	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < ENEMY_NUM)
	{
		j = i;
		while (j < ENEMY_NUM)
		{
			if (cube->enemy[j].player_dst > cube->enemy[i].player_dst)
			{
				tmp = cube->enemy[i];
				cube->enemy[i] = cube->enemy[j];
				cube->enemy[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sk_check_enemies(t_cube *cube, int i)
{
	if (is_looking(cube, &cube->enemy[ENEMY_NUM - 1 - i])
		&& (cube->enemy[ENEMY_NUM - 1 - i].start_y < (cube->screen_height / 2))
		&& (cube->enemy[ENEMY_NUM - 1 - i].end_y > (cube->screen_height / 2))
		&& (cube->enemy[ENEMY_NUM - 1 - i].player_dst < cube->rays[cube->res
				/ 2].length))
	{
		printf("enemy %d attacked! enemy HP: %d\n", ENEMY_NUM - 1 - i,
			cube->enemy[ENEMY_NUM - 1 - i].HP);
		cube->enemy[ENEMY_NUM - 1 - i].HP -= cube->player.weapon.DMG;
	}
}

void	ft_draw_enemies(t_cube *cube)
{
	struct timeval	tv;
	int				i;

	gettimeofday(&tv, NULL);
	sk_order_enemies(cube);
	i = 0;
	if (cube->player.delay == true)
	{
		if ((int)(tv.tv_sec
			- cube->player.atk_time) >= cube->player.weapon.fire_rate)
			cube->player.delay = false;
	}
	while (i < ENEMY_NUM)
	{
		if (is_looking(cube, &cube->enemy[ENEMY_NUM - 1 - i])
			&& (cube->enemy[ENEMY_NUM - 1 - i].start_y < (cube->screen_height
					/ 2)) && (cube->enemy[ENEMY_NUM - 1
					- i].end_y > (cube->screen_height / 2)))
			if (cube->player.delay == true && cube->player.attacked == true)
				sk_check_enemies(cube, i);
		ft_enemy(cube, &cube->enemy[i], cube->texture4);
		i++;
	}
}

void	ft_draw_proj(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < MAX_PROJECTILES)
	{
		if (cube->projectiles[i].in_use == 1)
			ft_projectile(cube, &cube->projectiles[i]);
		i++;
	}
}

void	ft_projectile51(t_cube *cube, t_projectile *projectile, t_vars10 *vars)
{
	cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
		+ ((int)vars->start_x * 4) + 0] = (projectile->texture->pixels[vars->k
			+ 0] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
		+ ((int)vars->start_x * 4) + 1] = (projectile->texture->pixels[vars->k
			+ 1] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
		+ ((int)vars->start_x * 4) + 2] = (projectile->texture->pixels[vars->k
			+ 2] * vars->tmp) + (0x33 * (1.0 - vars->tmp));
	cube->prev_buffer[(cube->screen_width * (int)vars->start_y * 4)
		+ ((int)vars->start_x * 4) + 3] = projectile->texture->pixels[vars->k
		+ 3];
}
