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
	int				j;
	t_enemy			tmp;

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
