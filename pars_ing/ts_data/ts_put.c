/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:26:54 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:32:47 by oel-mado         ###   ########.fr       */
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
	nu->next = NULL;
	nu->map = NULL;
	return (nu);
}

t_nc	*ts_put(t_teto *teto)
{
	t_nc	*nu;

	nu = ts_make_mt_nu();
	if (!nu)
		return (NULL);
	nu->imgs[WA] = ts_get_img(teto, WA);
	if (!nu->imgs[WA])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[FL] = ts_get_img(teto, FL);
	if (!nu->imgs[FL])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[CI] = ts_get_img(teto, CI);
	if (!nu->imgs[CI])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[PR] = ts_get_img(teto, PR);
	if (!nu->imgs[PR])
		return (ts_free_one_nomap(nu), NULL);
	nu->imgs[EN] = ts_get_img(teto, EN);
	if (!nu->imgs[EN])
		return (ts_free_one_nomap(nu), NULL);
	return (nu);
}
