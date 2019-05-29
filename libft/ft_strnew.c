/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosadchu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:21:00 by kosadchu          #+#    #+#             */
/*   Updated: 2018/11/19 17:17:49 by kosadchu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*m;

	m = (char*)malloc(sizeof(char) * size + 1);
	if (!m)
		return (NULL);
	ft_bzero(m, size + 1);
	return (m);
}
