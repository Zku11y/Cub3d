/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_opn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:26:31 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/08 20:32:43 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ts_opn(char *path)
{
	int	fd;

	if (dot_chk(path))
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}
