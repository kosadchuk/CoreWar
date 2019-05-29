/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:39:42 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/20 17:39:45 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	new = (*f)(lst);
	tmp = new;
	lst = lst->next;
	while (lst)
	{
		new->next = (*f)(lst);
		new = new->next;
		lst = lst->next;
	}
	new->next = NULL;
	return (tmp);
}
