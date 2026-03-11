/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:29:18 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

void	ts_lstdelone(t_list *lst, void (*del)(void *))
{
	void	*who;

	if (!lst || !del)
		return ;
	who = lst->content;
	del(who);
	free (lst);
}
