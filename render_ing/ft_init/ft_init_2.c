/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 14:12:31 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 21:32:53 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_10(t_cube *cube, t_nc *nu)
{
	cube->texture2 = nu->txtrs[SO];
	cube->texture3 = nu->txtrs[WE];
	cube->texture4 = nu->txtrs[EA];
	ft_load_png(cube, &(cube->texture5), "./Monster_1.png");
	ft_load_png(cube, &(cube->texture6), "./job_app.png");
	ft_load_png(cube, &(cube->texture_died), "./you_died.png");
	ft_load_png(cube, &(cube->crosshair), "./crosshair_2.png");
	cube->line_girth = (int)(cube->screen_width / cube->res);
	if (cube->line_girth == 0)
		cube->line_girth = 1;
	cube->mlx = mlx_init(cube->screen_width_buff, cube->screen_height_buff,
			"cub3d", true);
	if (cube->mlx == NULL)
	{
		perror("mlx init error :");
		ft_clean(cube, cube->nu, 1); // call ft_clean
	}
	cube->image = mlx_new_image(cube->mlx, cube->screen_width_buff,
			cube->screen_height_buff);
	if (cube->image == NULL)
	{
		mlx_terminate(cube->mlx);
		perror("image init error :");
		ft_clean(cube, cube->nu, 1);  // call ft_clean
	}
}

void	ft_init_11(t_cube *cube, t_nc *nu)
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

void	ft_init_enemies_1(t_cube *cube, int i, mlx_texture_t *texture)
{
	cube->enemy[i].HP = 100;
	cube->enemy[i].blood_frame_index = 0;
	cube->enemy[i].dead = false;
	cube->enemy[i].delay = false;
	cube->enemy[i].atk_delay = 1;
	cube->enemy[i].DMG = 20;
	cube->enemy[i].hitbox_len = 50;
	cube->enemy[i].health_offset = 0;
	cube->enemy[i].health_animation = 0;
	cube->enemy[i].health = texture;
}

void	ft_init_enemies_2(t_cube *cube, unsigned long seed, int posY, int i)
{
	cube->enemy[i].health_spawn = false;
	if ((ft_rand(&seed) % 10) < 9)
		cube->enemy[i].health_spawn = true;
	cube->enemy[i].y = (posY);
	cube->enemy[i].player_dst = sqrt((cube->player.x - cube->enemy[i].x)
			* (cube->player.x - cube->enemy[i].x) + (cube->player.y
				- cube->enemy[i].y) * (cube->player.y - cube->enemy[i].y));
	cube->enemy[i].max_hit_angle = atan2((cube->enemy[i].hitbox_len / 2.0),
			cube->enemy[i].player_dst);
}

void	ft_init_enemies(t_cube *cube)
{
	struct timeval	tv;
	unsigned long	seed;
	mlx_texture_t	*health_tex;

	int (i), (posX), (posY);
	i = 0;
	gettimeofday(&tv, NULL);
	seed = (unsigned long)tv.tv_usec / 100;
	ft_load_png(cube, &(health_tex), "./white_monster_2.png");
	while (i < ENEMY_NUM)
	{
		ft_init_enemies_1(cube, i, health_tex);
		posX = (int)(ft_rand(&seed) % (int)(cube->map_x * GRID_SIZE));
		posY = (int)(ft_rand(&seed) % (int)(cube->map_y * GRID_SIZE));
		while (cube->map[(int)(posY / GRID_SIZE)][(int)(posX
				/ GRID_SIZE)] == '1' || (posX >= (cube->map_x * GRID_SIZE)
				|| posY >= (cube->map_y * GRID_SIZE)))
		{
			posX = (int)(ft_rand(&seed) % (int)(cube->map_x * GRID_SIZE));
			posY = (int)(ft_rand(&seed) % (int)(cube->map_y * GRID_SIZE));
		}
		cube->enemy[i].x = (posX);
		ft_init_enemies_2(cube, seed, posY, i);
		i++;
	}
}
