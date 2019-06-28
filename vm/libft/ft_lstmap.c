/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:57:39 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:57:50 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	ft_lstmap(t_list *lst, t_lst_map_f f)
{
	t_list		new_list;
	t_list_elem	*elem;
	t_list_elem	*start;

	start = lst->start;
	ft_bzero(&new_list, sizeof(t_list));
	new_list.start = f(start);
	elem = new_list.start;
	while (start->next)
	{
		elem->next = f(start->next);
		elem = elem->next;
		start = start->next;
	}
	return (new_list);
}
