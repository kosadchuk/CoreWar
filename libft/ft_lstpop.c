/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:58:25 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:58:31 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop_front(t_list *lst)
{
	t_list_elem *tmp;

	if (!lst->start)
		return ;
	tmp = lst->start;
	lst->start = lst->start->next;
	if (lst->start)
		lst->start->prev = NULL;
	else
		lst->end = NULL;
	ft_lstdel_one(&tmp, lst->del);
	--lst->list_size;
}

void	ft_lstpop_back(t_list *lst)
{
	t_list_elem *tmp;

	if (!lst->end)
		return ;
	tmp = lst->end;
	lst->end = lst->end->prev;
	if (lst->end)
		lst->end->prev = NULL;
	else
		lst->end = NULL;
	ft_lstdel_one(&tmp, lst->del);
	--lst->list_size;
}
