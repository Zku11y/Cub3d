/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:25:44 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:32:36 by oel-mado         ###   ########.fr       */
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
	pear->val = ts_get_val(lain);
	if (!pear->val)
		return (free(pear), NULL);
	return (pear);
}

t_teto	*ts_key(char *lain)
{
	int	i;

	i = ts_spaces_skip(lain);
	if (ts_strncmp(&lain[i], "WA ", 3) == 0)
		return (ts_get(&lain[i + 3], WA));
	if (ts_strncmp(&lain[i], "FL ", 3) == 0)
		return (ts_get(&lain[i + 3], FL));
	if (ts_strncmp(&lain[i], "CI ", 3) == 0)
		return (ts_get(&lain[i + 3], CI));
	if (ts_strncmp(&lain[i], "PR ", 3) == 0)
		return (ts_get(&lain[i + 3], PR));
	if (ts_strncmp(&lain[i], "EN ", 3) == 0)
		return (ts_get(&lain[i + 3], EN));
	return (NULL);
}
