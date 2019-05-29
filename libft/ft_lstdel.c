/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:32:39 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/20 18:29:26 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;
	t_list	*t;

	if (!alst || !*alst || !del)
		return ;
	lst = *alst;
	while (lst)
	{
		t = lst->next;
		(*del)(lst->content, lst->content_size);
		free(lst);
		lst = t;
	}
	*alst = NULL;
}
