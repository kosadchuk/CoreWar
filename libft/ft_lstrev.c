/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:58:59 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:59:09 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstrev_next(t_list *lst)
{
	t_list_elem *prev;
	t_list_elem *current;
	t_list_elem *next;

	prev = NULL;
	current = lst->start;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	lst->start = prev;
}

void		ft_lstrev(t_list *lst)
{
	t_list_elem	*current;
	t_list_elem	*prev;
	t_list_elem	*next;

	prev = NULL;
	current = lst->end;
	while (current)
	{
		next = current->prev;
		current->prev = prev;
		prev = current;
		current = next;
	}
	lst->end = prev;
	ft_lstrev_next(lst);
}
