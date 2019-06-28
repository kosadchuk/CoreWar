/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:09:30 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/27 13:18:42 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_fatal_exit_func g_fef = &ft_perror_exit;

void	*ft_memalloc(size_t size)
{
	char	*m;

	m = malloc(sizeof(*m) * size);
	if (!m)
		g_fef("malloc() failed");
	ft_bzero(m, size);
	return (m);
}
