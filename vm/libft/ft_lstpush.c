/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:58:44 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:58:50 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_front(t_list *lst, t_list_elem *new_obj)
{
	new_obj->prev = NULL;
	new_obj->next = lst->start;
	if (lst->start)
		lst->start->prev = new_obj;
	else
		lst->end = new_obj;
	lst->start = new_obj;
	++lst->list_size;
}

void	ft_lstpush_back(t_list *lst, t_list_elem *new_obj)
{
	new_obj->next = NULL;
	new_obj->prev = lst->end;
	if (lst->end)
		lst->end->next = new_obj;
	else
		lst->start = new_obj;
	lst->end = new_obj;
	++lst->list_size;
}
