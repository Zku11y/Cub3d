/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:26:54 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 00:24:01 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ts_get_img(t_teto *teto, t_key key)
{
	t_teto	*to;

	to = teto;
	while (to)
	{
		if (key == to->key)
			return (ts_strdup(to->val));
		to = to->next;
	}
	return (NULL);
}

t_nc	*ts_make_mt_nu(void)
{
	t_nc	*nu;

	nu = ts_calloc(1, sizeof(t_nc));
	if (!nu)
		return (NULL);
	nu->imgs[NO] = NULL;
	nu->imgs[SO] = NULL;
	nu->imgs[WE] = NULL;
	nu->imgs[EA] = NULL;
	nu->next = NULL;
	nu->map = NULL;
	return (nu);
}

int	ts_put_rgb(t_nc *nu, t_teto *teto)
{
	char	*f;
	char	*c;

	f = ts_get_img(teto, F);
	if (!f)
		return (ts_free_one_nomap(nu), 1);
	if (ts_rgb(f, &nu->flor_r, &nu->flor_g, &nu->flor_b))
		return (free(f), ts_free_one_nomap(nu), 1);
	free(f);
	c = ts_get_img(teto, C);
	if (!c)
		return (ts_free_one_nomap(nu), 1);
	if (ts_rgb(c, &nu->ceil_r, &nu->ceil_g, &nu->ceil_b))
		return (free(c), ts_free_one_nomap(nu), 1);
	free(c);
	return (0);
}

t_nc	*ts_put(t_teto *teto)
{
	t_nc	*nu;

	nu = ts_make_mt_nu();
	if (!nu)
		return (NULL);
	nu->imgs[NO] = ts_get_img(teto, NO);
	if (!nu->imgs[NO])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[SO] = ts_get_img(teto, SO);
	if (!nu->imgs[SO])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[WE] = ts_get_img(teto, WE);
	if (!nu->imgs[WE])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[EA] = ts_get_img(teto, EA);
	if (!nu->imgs[EA])
		return (ts_free_one_nomap(nu), NULL);
	if (ts_put_rgb(nu, teto))
		return (NULL);
	return (nu);
}
