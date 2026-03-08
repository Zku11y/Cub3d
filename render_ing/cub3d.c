/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:13:24 by mdakni            #+#    #+#             */
/*   Updated: 2026/03/08 17:36:02 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void ft_update(void *param)
{
	t_cube *cube;
	struct timeval tv;

	cube = (t_cube *)param;
	gettimeofday(&tv, NULL);
 	if(cube->state != cube->prev_state)
		state_transition(cube, cube->state);
	state_machine(cube);

	cube->final_t = tv.tv_sec;
	cube->fps++;
	if(cube->final_t - cube->init_t == 1)
	{
		printf("fps : %d, player HP : %d, player angle : %lf\n", cube->fps, cube->player.HP, cube->player.angle);
		cube->init_t = cube->final_t;
		cube->fps = 0;
	}
}

void ft_init(t_cube *cube, t_nc *nu){
	ft_init_0(cube, nu);
	ft_init_1(cube, nu);
	ft_init_2(cube, nu);
	ft_init_3(cube, nu);
	ft_init_4(cube, nu);
	ft_init_5(cube, nu);
	ft_init_6(cube, nu);
	ft_init_7(cube, nu);
	ft_init_8(cube, nu);
	ft_init_9(cube, nu);
	ft_init_10(cube, nu);
	ft_init_11(cube, nu);
}


void f(){
	system("leaks -q cub3d");
}

void ts_print_nu(t_nc *nu)
{
	t_nc *ts;
	int i;
	int x;

	ts = nu;
	i = 0;
	if (!ts)
		return ts_putstr_fd("nu is NULL\n", 2);
	ts_putstr_fd("\n", 1); 
	ts_putstr_fd("ts START::\n", 1);
	while (ts)
	{
		ts_putstr_fd("nu=", 1);
		ts_putnbr_fd(i, 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("NO ", 1);
		ts_putstr_fd(ts->imgs[NO], 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("SO ", 1);
		ts_putstr_fd(ts->imgs[SO], 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("WE ", 1);
		ts_putstr_fd(ts->imgs[WE], 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("EA ", 1);
		ts_putstr_fd(ts->imgs[EA], 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("F::", 1);
		ts_putstr_fd("R", 1);
		ts_putnbr_fd(ts->flor_r, 1);
		ts_putstr_fd("G", 1);
		ts_putnbr_fd(ts->flor_g, 1);
		ts_putstr_fd("B", 1);
		ts_putnbr_fd(ts->flor_b, 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("C::", 1);
		ts_putstr_fd("R", 1);
		ts_putnbr_fd(ts->ceil_r, 1);
		ts_putstr_fd("G", 1);
		ts_putnbr_fd(ts->ceil_g, 1);
		ts_putstr_fd("B", 1);
		ts_putnbr_fd(ts->ceil_b, 1);
		ts_putstr_fd("|\n", 1);
		ts_putstr_fd("x", 1);
		ts_putnbr_fd(ts->x, 1);
		ts_putstr_fd(" |", 1);
		ts_putstr_fd("y", 1);
		ts_putnbr_fd(ts->y, 1);
		ts_putstr_fd("|\n", 1);
		ts_putchar_fd(ts->hi->who, 1);
		ts_putstr_fd("::", 1);
		ts_putstr_fd("x", 1);
		ts_putnbr_fd(ts->hi->x, 1);
		ts_putstr_fd("|y", 1);
		ts_putnbr_fd(ts->hi->y, 1);
		ts_putstr_fd("|\n", 1);
		x = 0;
		while (ts->map[x])
		{
			ts_putstr_fd("|", 1);
			ts_putstr_fd(ts->map[x], 1);
			ts_putstr_fd("|\n", 1);
			x++;
		}
		ts_putstr_fd("\n", 1);
		ts_putstr_fd("end.\n", 1);
		ts = ts->next;
		i++;
	}
	ts_putstr_fd("ts END.\n", 1);
}

void feet()
{
    system("leaks cub3d");
}

int main(int ac, char **av)
{
	t_nc *nu;

	nu = NULL;
    atexit(feet);
	if (ac < 2)
	return 1;
	t_cube *cube;
	cube = ts_calloc(sizeof(t_cube), 1);
	if(!cube)
		return 1;
	printf("before\n");
	nu = ts_pars(&av[1]);
	if (!nu)
	return 1;
	printf("after\n");
	ts_print_nu(nu); // -- ts just prnt REMOVE IT
	ft_map_init(cube, nu);

	int y = 0;
	int x = 0;

	while(y < nu->y){
		x = 0;
		while(x < nu->x){
			if(nu->map[y][x] == '1')
				printf("\e[1;31m1\e[0m");
			else
				printf("\e[1;32m%c\e[0m", nu->map[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}

	ft_init(cube, nu);
	printf("player pos (%lf, %lf), parse pos (%d, %d)\n", cube->player.x, cube->player.y, nu->hi->x, nu->hi->y);
	mlx_loop_hook(cube->mlx, ft_update, cube);
	mlx_loop(cube->mlx);
	mlx_terminate(cube->mlx);
	free_nu(nu);
	free(cube);
	return 0;
}















