/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:57:23 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:57:29 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, t_lst_iter_f f)
{
	t_list_elem *start;

	start = lst->start;
	while (start)
	{
		f(start);
		start = start->next;
	}
}
