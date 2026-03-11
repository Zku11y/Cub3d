/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_val.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:14:59 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:33:11 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ts_spaces_skip(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' '
			|| (str[i] >= 9 && str[i] <= 13)))
		i++;
	return (i);
}

char	*ts_get_val(char *str)
{
	int	i;
	int	j;
	int	l;

	j = 0;
	l = 0;
	if (!str)
		return (NULL);
	i = ts_spaces_skip(str);
	if (!str[i])
		return (NULL);
	l = i;
	while (str[l] && !(str[l] == ' '
			|| (str[l] >= 9 && str[l] <= 13)))
		l++;
	j = l + ts_spaces_skip(&str[l]);
	if (str[j])
		return (NULL);
	return (ts_strndup(&str[i], l - i));
}
