/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nu_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:32:42 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:32:30 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_mp(t_mp *mp)
{
	t_mp	*ts;

	while (mp)
	{
		if (mp->val)
			free(mp->val);
		ts = mp;
		mp = mp->next;
		free(ts);
	}
}

void	free_nu_map(char **nu)
{
	int	i;

	i = 0;
	while (nu[i])
	{
		free(nu[i]);
		i++;
	}
	free(nu);
}
