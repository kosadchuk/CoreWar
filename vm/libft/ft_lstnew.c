/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:58:04 by kosadchu          #+#    #+#             */
/*   Updated: 2019/06/01 11:58:09 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_elem	*ft_lstnew(void const *content, size_t content_size)
{
	t_list_elem	*new_obj;
	void		*data;

	data = NULL;
	if (content)
	{
		data = ft_memalloc(content_size);
		ft_memcpy(data, content, content_size);
	}
	else
		content_size = 0;
	new_obj = (t_list_elem *)ft_memalloc(sizeof(t_list_elem));
	new_obj->content = data;
	new_obj->content_size = content_size;
	return (new_obj);
}

t_list_elem	*ft_lstnew_ref(void *content, size_t content_size)
{
	t_list_elem	*new_obj;

	if (!content)
		content_size = 0;
	new_obj = (t_list_elem *)ft_memalloc(sizeof(t_list_elem));
	new_obj->content = content;
	new_obj->content_size = content_size;
	return (new_obj);
}
