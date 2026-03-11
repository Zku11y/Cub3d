/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdakni <mdakni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:26:54 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/10 02:21:06 by mdakni           ###   ########.fr       */
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
	nu->imgs[WA] = NULL;
	nu->imgs[FL] = NULL;
	nu->imgs[CI] = NULL;
	nu->imgs[PR] = NULL;
	nu->imgs[EN] = NULL;
	nu->imgs[ED] = NULL;
	nu->imgs[HP] = NULL;
	nu->next = NULL;
	nu->map = NULL;
	return (nu);
}

t_nc	*ts_put(t_teto *teto)
{
	t_nc	*nu;
	int		i;

	i = WA;
	nu = ts_make_mt_nu();
	if (!nu)
		return (NULL);
	while (i <= HP)
	{
		nu->imgs[i] = ts_get_img(teto, i);
		if (!nu->imgs[i])
			return (ts_free_one_nomap(nu), ts_cln_pngs(nu), NULL);
		i++;
	}
	return (nu);
}
