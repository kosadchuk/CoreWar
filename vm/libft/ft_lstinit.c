/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:57:01 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:57:09 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstinit(t_list *lst, t_delptr del_list_func)
{
	ft_bzero(lst, sizeof(t_list));
	lst->del = del_list_func;
}
