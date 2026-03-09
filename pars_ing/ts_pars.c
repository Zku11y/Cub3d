/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skully <skully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 23:05:20 by oel-mado          #+#    #+#             */
/*   Updated: 2026/03/09 20:19:20 by skully           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ts_free_one_nomap(t_nc *nu)
{
	free(nu->imgs[WA]);
	free(nu->imgs[FL]);
	free(nu->imgs[CI]);
	free(nu->imgs[PR]);
	free(nu->imgs[EN]);
	free(nu->imgs[ED]);
	free(nu);
}

void	free_nu(t_nc *nu)
{
	t_nc	*ts;

	while (nu)
	{
		ts = nu;
		nu = nu->next;
		free(ts->start);
		free(ts->end);
		free_nu_map(ts->map);
		ts_cln_pngs(ts);
		ts_free_one_nomap(ts);
		// free(ts);
	}
}

t_nc	*ts_nu(char *lain)
{
	t_nc	*nu;
	int		fd;

	fd = ts_opn(lain);
	if (fd == -1)
		return (ts_putstr_fd("cant open\n", 2), NULL);
	nu = ts_make_one(fd);
	close(fd);
	if (!nu)
		return (NULL);
	return (nu);
}

t_nc	*ts_pars(char **arg)
{
	int		i;
	t_nc	*hd;
	t_nc	*nu;

	i = 1;
	hd = ts_nu(arg[0]);
	if (!hd)
		return (NULL);
	nu = hd;
	while (arg[i])
	{
		nu->next = ts_nu(arg[i]);
		if (!nu->next)
			break ;
		nu = nu->next;
		i++;
	}
	printf("DS::x%d,y%d\n", nu->start->d_x, nu->start->d_y);
	printf("DE::x%d,y%d\n", nu->end->d_x, nu->end->d_y);
	return (hd);
}
