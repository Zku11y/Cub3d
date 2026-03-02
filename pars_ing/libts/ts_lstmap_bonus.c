/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ts_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-mado <oel-mado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 14:29:37 by oel-mado          #+#    #+#             */
/*   Updated: 2026/01/15 05:07:51 by oel-mado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libts.h"

t_list	*ts_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*hd;
	void	*cnt;

	hd = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		cnt = f(lst->content);
		new = ts_lstnew(cnt);
		if (!new)
		{
			free (cnt);
			ts_lstclear(&hd, del);
			return (NULL);
		}
		ts_lstadd_back(&hd, new);
		lst = lst->next;
	}
	return (hd);
}
