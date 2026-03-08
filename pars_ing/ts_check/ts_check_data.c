/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_check_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:15:29 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/07 23:16:29 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ts_cln_pngs(t_nc *nu)
{
	int	i;

	i = NO;
	while (i < EA && nu->txtrs[i])
	{
		mlx_delete_texture(nu->txtrs[i]);
		i++;
	}
}

int	ts_check_data(t_nc *nu)
{
	int	i;

	i = NO;
	if (!nu)
		return (1);
	if (!nu->imgs[NO] || !nu->imgs[SO]
		|| !nu->imgs[WE] || !nu->imgs[EA])
		return (1);
	while (i <= EA)
	{
		nu->txtrs[i] = mlx_load_png(nu->imgs[i]);
		if (!nu->txtrs[i])
			return (ts_cln_pngs(nu), 1);
		i++;
	}
	return (0);
}
