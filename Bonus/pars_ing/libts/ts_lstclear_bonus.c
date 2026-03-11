/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:29:14 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

void	ts_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*fr;
	t_list	*nxt;

	if (!lst || !(*lst) || !del)
		return ;
	nxt = *lst;
	while (nxt)
	{
		fr = nxt;
		del(nxt->content);
		nxt = nxt->next;
		free (fr);
	}
	*lst = NULL;
}
