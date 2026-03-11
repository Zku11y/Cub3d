/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:25:44 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/07 23:26:18 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_teto	*ts_get(char *lain, t_key key)
{
	t_teto	*pear;

	pear = ts_calloc(1, sizeof(t_teto));
	if (!pear)
		return (NULL);
	pear->key = key;
	pear->next = NULL;
	if (key == F || key == C)
		pear->val = ts_get_rgb_val(lain);
	else
		pear->val = ts_get_val(lain);
	if (!pear->val)
		return (free(pear), NULL);
	return (pear);
}

t_teto	*ts_key(char *lain)
{
	int	i;

	i = ts_spaces_skip(lain);
	if (ts_strncmp(&lain[i], "NO ", 3) == 0)
		return (ts_get(&lain[i + 3], NO));
	if (ts_strncmp(&lain[i], "SO ", 3) == 0)
		return (ts_get(&lain[i + 3], SO));
	if (ts_strncmp(&lain[i], "WE ", 3) == 0)
		return (ts_get(&lain[i + 3], WE));
	if (ts_strncmp(&lain[i], "EA ", 3) == 0)
		return (ts_get(&lain[i + 3], EA));
	if (ts_strncmp(&lain[i], "F ", 2) == 0)
		return (ts_get(&lain[i + 2], F));
	if (ts_strncmp(&lain[i], "C ", 2) == 0)
		return (ts_get(&lain[i + 2], C));
	return (NULL);
}
