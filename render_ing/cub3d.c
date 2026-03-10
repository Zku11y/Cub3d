/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/10 03:50:51 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_update(void *param)
{
	t_cube			*cube;
	struct timeval	tv;

	cube = (t_cube *)param;
	gettimeofday(&tv, NULL);
	if (cube->state != cube->prev_state && cube->transition == 0)
	{
		state_transition(cube, cube->state);
		cube->trans_dst = (cube->screen_width_buff / 2);
	}
	state_machine(cube);
	cube->final_t = tv.tv_sec;
	cube->fps++;
	if (cube->final_t - cube->init_t == 1)
	{
		printf("fps : %d, player HP : %d, player angle : %lf\n", cube->fps,
			cube->player.HP, cube->player.angle);
		cube->init_t = cube->final_t;
		cube->fps = 0;
	}
	if (mlx_is_key_down(cube->mlx, MLX_KEY_ESCAPE))
		ft_clean(cube, cube->nu, 0);
}

void	ft_init(t_cube *cube, t_nc *nu)
{
	ft_init_0(cube, nu);
	ft_init_1(cube, nu);
	ft_init_2(cube, nu);
	ft_init_3(cube);
	ft_init_4(cube);
	ft_init_5(cube);
	ft_init_6(cube);
	ft_init_7(cube);
	ft_init_8(cube);
	ft_init_9(cube, nu);
	ft_init_10(cube, nu);
	ft_init_11(cube);
}

void	feet(void)
{
	system("leaks cub3d");
}

int	main(int ac, char **av)
{
	t_nc	*nu;
	t_cube	*cube;

	nu = NULL;
	atexit(feet);
	if (ac < 2)
		return (1);
	cube = ts_calloc(sizeof(t_cube), 1);
	if (!cube)
		return (1);
	printf("before\n");
	nu = ts_pars(&av[1]);
	if (!nu)
		return (1);
	cube->nu = nu;
	cube->map = nu->map;
	ft_init(cube, nu);
	mlx_loop_hook(cube->mlx, ft_update, cube);
	mlx_loop(cube->mlx);
	ft_clean(cube, nu, 0);
	return (0);
}
