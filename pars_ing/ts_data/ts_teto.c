/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_teto.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:14:15 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:33:05 by oel-mado         ###   ########.fr       */
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
	if (rec_map(nu->map, nu))
	{
		free_nu_map(nu->map);
		ts_free_one_nomap(nu);
		ts_putstr_fd("ASS MAP\n", 2);
		return (NULL);
	}
	return (nu);
}
