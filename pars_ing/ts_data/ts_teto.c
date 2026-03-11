/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_teto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:14:15 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/11 02:10:43 by mdakni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_nc	*ts_make_one(int fd)
{
	t_teto	*ts;
	t_nc	*nu;

	ts = ts_read(fd);
	if (!ts)
		return (NULL);
	nu = ts_put(ts);
	ts_free_pear(ts);
	if (!nu)
		return (NULL);
	if (ts_check_data(nu))
		return (ts_free_one_nomap(nu), NULL);
	if (get_map(fd, nu))
		return (ts_free_one_nomap(nu), NULL);
	if (ts_edg_chk(nu->map, nu->x, nu->y) || rec_map(nu->map, nu))
	{
		free_nu_map(nu->map);
		ts_cln_pngs(nu);
		ts_free_one_nomap(nu);
		return (NULL);
	}
	return (nu);
}

char	*get_lain_with_space(int fd)
{
	char	*lain;

	if (fd < 0)
		return (NULL);
	lain = gnl(fd);
	if (!lain)
		return (NULL);
	return (lain);
}
